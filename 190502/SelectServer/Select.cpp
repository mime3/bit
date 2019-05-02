#pragma comment(lib, "ws2_32.lib") // 프로젝트 속성, 링커, 입력
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE	1024
#define PORT	40100

struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvBytes;
	int sendBytes;
};

SOCKET listenSock;
int nTotalSockets = 0;
SOCKETINFO* SocketInfoArray[FD_SETSIZE];

void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& pMsg, 0, NULL);

	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

bool CreateListenSocket()
{
	int retval;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return false;
	}

	u_long on = 1;
	retval = ioctlsocket(listenSock, FIONBIO, &on);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return false;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	retval = bind(listenSock, (SOCKADDR*)& serveraddr, sizeof(serveraddr));
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

BOOL AddSocketInfo(SOCKET sock)
{
	if (nTotalSockets >= (FD_SETSIZE - 1))
	{
		printf("소켓정보를 추가할 수 없습니다.\n");
		return FALSE;
	}

	SOCKETINFO* ptr = new SOCKETINFO;
	if (ptr == NULL)
	{
		printf("메모리가 부족합니다.\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvBytes = 0;
	ptr->sendBytes = 0;
	SocketInfoArray[nTotalSockets++] = ptr;
	return TRUE;
}

void RemoveSocketInfo(int nIndex)
{
	SOCKETINFO* ptr = SocketInfoArray[nIndex];

	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(clientAddr);
	getpeername(ptr->sock, (SOCKADDR*) &clientAddr, &addrLen);
	printf("클라이언트 종료 : IP = %s, PORT = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	closesocket(ptr->sock);
	delete ptr;

	for (int i = nIndex; i < nTotalSockets; i++)
	{
		SocketInfoArray[i] = SocketInfoArray[i + 1];
	}
	nTotalSockets--;
}

UINT WINAPI WorkerThread(LPVOID lpParam)
{
	int retval;
	FD_SET rset;
	FD_SET wset;
	SOCKET clientSock;
	SOCKADDR_IN clientAddr;
	int addrLen;

	while (true)
	{
		FD_ZERO(&rset);
		FD_ZERO(&wset);

		FD_SET(listenSock, &rset);
		for (int i = 0; i < nTotalSockets; i++)
		{
			if (SocketInfoArray[i]->recvBytes > SocketInfoArray[i]->sendBytes)
				FD_SET(SocketInfoArray[i]->sock, &wset);
			else
				FD_SET(SocketInfoArray[i]->sock, &rset);
		}

		retval = select(0, &rset, &wset, NULL, NULL);
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			break;
		}
		if (FD_ISSET(listenSock, &rset))
		{
			addrLen = sizeof(clientAddr);
			clientSock = accept(listenSock, (SOCKADDR*)& clientAddr, &addrLen);
			if (clientSock == INVALID_SOCKET)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					DisplayMessage();
			}
			else
			{
				printf("[SERVER] Connect Client : IP = %s, PORT = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
				if (AddSocketInfo(clientSock) == FALSE)
				{
					printf("[SERVER] DisConnect\n");
					closesocket(clientSock);
				}
			}
		}
		for (int i = 0; i < nTotalSockets; i++)
		{
			SOCKETINFO* ptr = SocketInfoArray[i];
			if (FD_ISSET(ptr->sock, &rset))
			{
				retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						DisplayMessage();
						RemoveSocketInfo(i);
					}
					continue;
				}
				else if (retval == 0)
				{
					RemoveSocketInfo(i);
					continue;
				}
				ptr->recvBytes = retval;
				addrLen = sizeof(clientAddr);

				getpeername(ptr->sock, (SOCKADDR*)& clientAddr, &addrLen);
				ptr->buf[retval] = 0;

				printf("[SERVER] IP = %s, PORT = %d, MESSAGE = %s\n",
					inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port),
					ptr->buf);
			}
			if (FD_ISSET(ptr->sock, &wset))
			{
				retval = send(ptr->sock, ptr->buf + ptr->sendBytes, ptr->recvBytes - ptr->sendBytes, 0);
				if (retval == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						DisplayMessage();
						RemoveSocketInfo(i);
					}
					continue;
				}
				ptr->sendBytes += retval;
				if (ptr->recvBytes == ptr->sendBytes)
				{
					ptr->recvBytes = ptr->sendBytes = 0;
				}
			}
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

	if (!CreateListenSocket())
	{
		printf("fail\n");
		return -1;
	}

	UINT threadID;
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, WorkerThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}