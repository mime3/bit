#pragma comment(lib,"ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE	1024
#define PORT	40100

struct SOCKETINFO;

SOCKET listenSock;
int totalSocket = 0;
SOCKETINFO* socketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT eventArray[WSA_MAXIMUM_WAIT_EVENTS];

struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvByte;
	int sendByte;
};

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& pMsg, 0, NULL);

	printf("%s\n", (char *)pMsg);
	LocalFree(pMsg);
}

BOOL AddSocketInfo(SOCKET sock)
{
	if (totalSocket >= WSA_MAXIMUM_WAIT_EVENTS)
	{
		printf("[오류] 소켓 정보 추가 불가\n");
		return FALSE;
	}

	SOCKETINFO* newInfo = new SOCKETINFO;
	if (newInfo == NULL)
	{
		printf("[오류] 메모리가 부족합니다\n");
		return FALSE;
	}

	WSAEVENT eventHandle = WSACreateEvent();
	if (eventHandle == WSA_INVALID_EVENT)
	{
		DisplayMessage();
		return FALSE;
	}

	newInfo->sock = sock;
	newInfo->recvByte = 0;
	newInfo->sendByte = 0;
	socketInfoArray[totalSocket] = newInfo;
	eventArray[totalSocket] = eventHandle;
	totalSocket++;
	return TRUE;
}

void RemoveSocketInfo(int index)
{
	SOCKETINFO* target = socketInfoArray[index];

	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(clientAddr);
	getpeername(target->sock, (SOCKADDR*)& clientAddr, &addrLen);
	printf("[Server] 클라이언트 종료: IP = %s, 포트 = %d\n",
		inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	closesocket(target->sock);
	delete target;
	WSACloseEvent(eventArray[index]);

	for (int i = index; i < totalSocket; i++)
	{
		socketInfoArray[i] = socketInfoArray[i + 1];
		eventArray[i] = eventArray[i + 1];
	}
	totalSocket--;
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

	retval = WSAEventSelect(listenSock, eventArray[totalSocket - 1], FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}

	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	retval = bind(listenSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}

	retval = listen(listenSock, SOMAXCONN);
	if(retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}
	return true;
}

UINT WINAPI WorkerThread(LPVOID lpParam)
{
	int retval;
	int index;
	WSANETWORKEVENTS networkEvent;
	SOCKET clientSock;
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(clientAddr);

	while (true)
	{
		index = WSAWaitForMultipleEvents(totalSocket, eventArray, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED)
		{
			DisplayMessage();
			continue;
		}
		index -= WSA_WAIT_EVENT_0;

		retval = WSAEnumNetworkEvents(socketInfoArray[index]->sock, eventArray[index], &networkEvent);
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			continue;
		}

		if (networkEvent.lNetworkEvents & FD_ACCEPT)
		{
			if (networkEvent.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				DisplayMessage();
				continue;
			}
			clientSock = accept(socketInfoArray[index]->sock, (SOCKADDR*)& clientAddr, &addrLen);
			if (clientSock == INVALID_SOCKET)
			{
				DisplayMessage();
				continue;
			}
			printf("[Server] 클라이언트 접속: IP = %s, PORT = %d\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

			if (totalSocket >= WSA_MAXIMUM_WAIT_EVENTS)
			{
				printf("[오류] 더 이상 접속을 받아들일 수 없습니다.\n");
				closesocket(clientSock);
				continue;
			}

			if (AddSocketInfo(clientSock) == FALSE)
				continue;

			retval = WSAEventSelect(clientSock, eventArray[totalSocket - 1], FD_READ | FD_WRITE | FD_CLOSE);
			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				break;
			}
		}
		if (networkEvent.lNetworkEvents & FD_READ || networkEvent.lNetworkEvents & FD_WRITE)
		{
			if (networkEvent.lNetworkEvents & FD_READ && networkEvent.iErrorCode[FD_READ_BIT] != 0)
			{
				DisplayMessage();
				continue;
			}

			if (networkEvent.lNetworkEvents & FD_WRITE && networkEvent.iErrorCode[FD_WRITE_BIT] != 0)
			{
				DisplayMessage();
				continue;
			}

			SOCKETINFO* ptr = socketInfoArray[index];

			if (ptr->recvByte == 0)
			{
				retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						DisplayMessage();
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->recvByte = retval;
			}

			if (ptr->recvByte > ptr->sendByte)
			{
				retval = send(ptr->sock, ptr->buf, ptr->recvByte - ptr->sendByte, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						DisplayMessage();
						RemoveSocketInfo(index);
					}
					continue;
				}
				ptr->sendByte += retval;

				if (ptr->recvByte == ptr->sendByte)
					ptr->recvByte = ptr->sendByte = 0;
			}
		}

		if (networkEvent.lNetworkEvents & FD_CLOSE)
		{
			if (networkEvent.iErrorCode[FD_CLOSE_BIT] != 0)
				DisplayMessage();
			RemoveSocketInfo(index);
		}
	}
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

	if (!CreateListenSocket())
	{
		printf("fail\n");
		return -1;
	}

	UINT threadID;
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
}
