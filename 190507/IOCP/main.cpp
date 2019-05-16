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

SOCKET listenSock;

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& pMsg, 0, NULL);

	printf("%s\n", (char*)pMsg);
	LocalFree(pMsg);
}

UINT WINAPI WorkerThread(LPVOID lpParam)
{
	HANDLE hcp = (HANDLE)lpParam;
	int retval;

	while (true)
	{
		DWORD cbTransferred;
		SOCKET clientSock;
		SOCKETINFO* ptr;
		retval = GetQueuedCompletionStatus(hcp, &cbTransferred, &clientSock, (LPOVERLAPPED*)& ptr, INFINITE);

		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(clientAddr);
		getpeername(clientSock, (SOCKADDR*)& clientAddr, &addrLen);

		if (retval == FALSE || cbTransferred == 0)
		{
			if (retval == FALSE)
			{
				DWORD temp1, temp2;
				WSAGetOverlappedResult(ptr->sock, &(ptr->overlapped), &temp1, FALSE, &temp2);
				DisplayMessage();
			}
			closesocket(ptr->sock);

			printf("[Server] 클라이언트 종료: IP = %s, 포트 = %d\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

			delete ptr;
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
		{
			ptr->sendByte += cbTransferred;
		}

		if (ptr->recvByte > ptr->sendByte)
		{
			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf + ptr->sendByte;
			ptr->wsabuf.len = ptr->recvByte - ptr->sendByte;

			DWORD sendBytes;
			retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendBytes, 0, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					DisplayMessage();
				}
				continue;
			}
		}
		else
		{
			ptr->recvByte = 0;

			ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = BUFFERSIZE;
			DWORD recvBytes;
			DWORD flag = 0;
			retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvBytes, &flag, &(ptr->overlapped), NULL);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					DisplayMessage();
				}
				continue;
			}
		}
	}
	return 0;
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

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("fail\n");
		return -1;
	}

	HANDLE hcp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (hcp == NULL)
		return -1;

	SYSTEM_INFO si;
	GetSystemInfo(&si);

	HANDLE thread;
	UINT threadID;
	for (int i = 0; i < si.dwNumberOfProcessors; i++)
	{
		CloseHandle((HANDLE)_beginthreadex(0, 0, WorkerThread, (void*)hcp, 0, &threadID));
	}

	if (!CreateListenSocket())
	{
		printf("fail\n");
		return -1;
	}

	while (true)
	{
		int retval;
		SOCKADDR_IN	clientAddr;
		int addrLen = sizeof(clientAddr);
		SOCKET clientSock = accept(listenSock, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}
		printf("[Server] 클라이언트 접속: IP = %s, PORT = %d\n",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		HANDLE hResult = CreateIoCompletionPort((HANDLE)clientSock, hcp, (DWORD)clientSock, 0);
		if (hResult == NULL)
			return -1;

		SOCKETINFO* ptr = new SOCKETINFO;
		if (ptr == NULL)
		{
			printf("[오류] 메모리 부족\n");
			return -1;
		}
		ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		ptr->sock = clientSock;
		ptr->recvByte = 0;
		ptr->sendByte = 0;
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = BUFFERSIZE;

		DWORD recvBytes;
		DWORD flag = 0;
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &recvBytes, &flag, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSA_IO_PENDING)
			{
				DisplayMessage();
			}
			continue;
		}
	}
	WSACleanup();
	return 0;
}