#pragma comment(lib, "ws2_32.lib") // 프로젝트 속성, 링커, 입력
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>

#define BUFFERSIZE	1024
#define PORT	40100

SOCKET listenSock;

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


UINT WINAPI ComThread(LPVOID lpParam)
{
	SOCKET clientSock = (SOCKET)lpParam;
	int recvByte;
	char buf[BUFFERSIZE];
	SOCKADDR_IN clientAddr;

	while (true)
	{
		recvByte = recv(clientSock, buf, BUFFERSIZE, 0);
		if (recvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				DisplayMessage();
				break;
			}
			continue;
		}
		else if (recvByte == 0)
		{
			DisplayMessage();
			break;
		}
		int addrLen = sizeof(clientAddr);
		int retval = getpeername(clientSock, (SOCKADDR*)& clientAddr, &addrLen);
		if (retval == SOCKET_ERROR)
		{
			DisplayMessage();
			continue;
		}
		buf[recvByte] = 0;
		printf("[SERVER] Client: IP = %s, Port = %d, Message : %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buf);
		retval = send(clientSock, buf, recvByte, 0);
		if (retval == SOCKET_ERROR)
		{
			//if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				DisplayMessage();
				break;
			}
		}
	}
	closesocket(clientSock);
	printf("\n[SERVER] DisConnect Client: IP = %s, Port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	return 0;
}

UINT WINAPI ListenThread(LPVOID lpParam)
{
	while (true)
	{
		int retval;
		SOCKET clientSock;
		SOCKADDR_IN clientAddr;
		int addrlen = sizeof(clientAddr);
		char buf[BUFFERSIZE];
		clientSock = accept(listenSock, (SOCKADDR*)& clientAddr, &addrlen);
		if (clientSock == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				DisplayMessage();
			}
			continue;
		}

		printf("\n[SERVER] Connect Client: IP = %s, Port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		UINT threadID;
		HANDLE thread = (HANDLE)_beginthreadex(0, 0, ComThread, (void*)clientSock, 0, &threadID);
		CloseHandle(thread);
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
	WaitForSingleObject((HANDLE)_beginthreadex(0, 0, ListenThread, 0, 0, &threadID), INFINITE);
	WSACleanup();
	return 0;
}