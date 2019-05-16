#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE	1024
#define PORT	40100

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvByte;
	int sendByte;
	WSABUF wsabuf;
};

CRITICAL_SECTION cs;
SOCKET listenSock;
int totalSocket = 0;
SOCKETINFO* socketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT eventArray[WSA_MAXIMUM_WAIT_EVENTS];

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& pMsg, 0, NULL);

	printf("%s\n", (char*)pMsg);
	LocalFree(pMsg);
}

BOOL AddSocketInfo(SOCKET sock)
{
	EnterCriticalSection(&cs);
	if (totalSocket >= WSA_MAXIMUM_WAIT_EVENTS)
	{
		printf("");
		return FALSE;
	}

	SOCKETINFO* ptr = new SOCKETINFO;
	if(ptr == NULL)
	{
		return FALSE;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT)
	{
		DisplayMessage();
		return FALSE;
	}

	ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
	ptr->overlapped.hEvent = hEvent;
	ptr->sock = sock;
	ptr->recvByte = 0;
	ptr->sendByte = 0;
	ptr->wsabuf.buf = ptr->buf;
	ptr->wsabuf.len = BUFFERSIZE;
	socketInfoArray[totalSocket] = ptr;
	eventArray[totalSocket] = hEvent;
	totalSocket++;
	LeaveCriticalSection(&cs);
	return TRUE;
}

void RemoveSocketInfo(int index)
{
	EnterCriticalSection(&cs);
	SOCKETINFO* ptr = socketInfoArray[index];
	closesocket(ptr->sock);
	delete ptr;
	WSACloseEvent(eventArray[index]);
	for (int i = index; i < totalSocket; i++)
	{
		socketInfoArray[i] = socketInfoArray[i + 1];
		eventArray[i] = eventArray[i + 1];
	}
	totalSocket--;
	LeaveCriticalSection(&cs);
}

bool CreateListenSocket()
{
	int retval;

	listenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return false;
	}

	if (AddSocketInfo(listenSock) == FALSE)
		return false;

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT)
	{
		DisplayMessage();
		return false;
	}
	eventArray[totalSocket++] = hEvent;

	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	retval = bind(listenSock, (SOCKADDR*)& serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}

	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	return true;
}

UINT WINAPI WorkerThread(LPVOID lpParam)
{
	int retval;

	while (true)
	{
		DWORD index = WSAWaitForMultipleEvents(totalSocket, eventArray, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED)
		{
			DisplayMessage();
			continue;
		}
		index -= WSA_WAIT_EVENT_0;
		WSAResetEvent(eventArray[index]);
		if (index == 0)
			continue;

		SOCKETINFO* ptr = socketInfoArray[index];
		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(clientAddr);
		getpeername(ptr->sock, (SOCKADDR*)& clientAddr, &addrLen);

		DWORD cbTransferred, flag;
		retval = WSAGetOverlappedResult(ptr->sock, &(ptr->overlapped), &cbTransferred, FALSE, &flag);
		if (retval == FALSE || cbTransferred == 0)
		{
			if (retval == FALSE)
				DisplayMessage();
			RemoveSocketInfo(index);
			printf("[Server] 클라이언트 종료: IP = %s, 포트 = %d\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
			continue;
		}
		if (ptr->recvByte == 0)
		{
			ptr->recvByte = cbTransferred;
			ptr->sendByte = 0;
			ptr->buf[ptr->recvByte] = 0;
			printf("[TCP/%s:%d] %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port),
				ptr->buf);
		}
		else
			ptr->sendByte += cbTransferred;

		if (ptr->recvByte > ptr->sendByte)
		{
			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->overlapped.hEvent = eventArray[index];
			ptr->wsabuf.buf = ptr->buf + ptr->sendByte;
			ptr->wsabuf.len = ptr->recvByte - ptr->sendByte;

			DWORD sendBytes;
			retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendBytes, 0, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
					DisplayMessage();
				continue;
			}
		}
		else
		{
			ptr->recvByte = 0;

			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->overlapped.hEvent = eventArray[index];
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = BUFFERSIZE;
			DWORD recvBytes;
			DWORD flag = 0;
			retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvBytes, &flag, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
					DisplayMessage();
				continue;
			}

		}
	}
}

UINT WINAPI ListenThread(LPVOID lpParam)
{
	while (true)
	{
		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(clientAddr);
		SOCKET clientSock = accept(listenSock, (SOCKADDR*)& clientAddr, &addrLen);
		if (clientSock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}
		printf("[Server] 클라이언트 접속: IP = %s, PORT = %d\n",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		if (AddSocketInfo(clientSock) == FALSE)
		{
			closesocket(clientSock);
			printf("[Server] 클라이언트 종료: IP = %s, 포트 = %d\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
			continue;
		}

		SOCKETINFO* ptr = socketInfoArray[totalSocket - 1];
		DWORD recvBytes;
		DWORD flags = 0;
		int retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvBytes, &flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				DisplayMessage();
				RemoveSocketInfo(totalSocket - 1);
				continue;
			}
		}

		if (WSASetEvent(eventArray[0]) == FALSE)
		{
			DisplayMessage();
			break;
		}
	}
	closesocket(listenSock);
	return 0;
}

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("fail\n");
		return -1;
	}

	InitializeCriticalSection(&cs);
	if (!CreateListenSocket())
	{
		printf("fail\n");
		return -1;
	}

	UINT threadID;
	HANDLE thread[2];
	thread[0] = (HANDLE)_beginthreadex(0, 0, ListenThread, 0, 0, &threadID);
	thread[1] = (HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID);

	WaitForMultipleObjects(2, thread, TRUE, INFINITE);
	DeleteCriticalSection(&cs);
	WSACleanup();
	return 0;
}