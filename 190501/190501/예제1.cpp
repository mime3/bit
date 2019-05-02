#pragma comment(lib, "ws2_32.lib") // 프로젝트 속성, 링커, 입력
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

#define BUFFERSIZE	1024
#define PORT	40100
void DisplayMessage()
{
	LPVOID pMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)& pMsg, 0, NULL);

	printf("%s\n", pMsg);
	LocalFree(pMsg);
}

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("fail\n");
		return -1;
	}

	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (listenSock == INVALID_SOCKET)
	{
		DisplayMessage();
		return -1;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int retval = bind(listenSock, (SOCKADDR*)& serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	retval = listen(listenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		DisplayMessage();
		return -1;
	}

	while (true)
	{
		SOCKADDR_IN clientAddr;
		int addrlen = sizeof(clientAddr);
		char buf[BUFFERSIZE];
		SOCKET clientSock = accept(listenSock, (SOCKADDR*)& clientAddr, &addrlen);
		if (clientSock == INVALID_SOCKET)
		{
			DisplayMessage();
			continue;
		}

		printf("\n[SERVER] Connect Client: IP = %s, Port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

		while (true)
		{
			retval = recv(clientSock, buf, BUFFERSIZE, 0);
			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				break;
			}
			else if (retval == 0)
			{
				DisplayMessage();
				break;
			}

			buf[retval] = 0;
			printf("[SERVER] Client: IP = %s, Port = %d, Message : %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buf);
		}
		closesocket(clientSock);
		printf("\n[SERVER] DisConnect Client: IP = %s, Port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	}

	closesocket(listenSock);
	WSACleanup();

	return 0;
}