#pragma comment(lib, "ws2_32.lib") // 프로젝트 속성, 링커, 입력
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

#define BUFFERSIZE 1024
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

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		return -1;
	}

	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int retval = connect(sock, (SOCKADDR*)& serverAddr, sizeof(serverAddr));

	if (retval == SOCKET_ERROR)
	{
		return -1;
	}

	char buf[BUFFERSIZE];
	int len;

	while (true)
	{
		ZeroMemory(buf, sizeof(buf));
		printf("Input data : ");
		if (fgets(buf, BUFFERSIZE, stdin) == NULL)
			break;

		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = 0;
		if (strlen(buf) == 0)
			break;

		retval = send(sock, buf, strlen(buf), 0);

		if (retval == SOCKET_ERROR)
		{
			break;
		}

		printf("[TCP Client] %d Byte Send", retval);
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}