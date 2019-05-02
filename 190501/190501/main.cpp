#pragma comment(lib, "ws2_32.lib") // 프로젝트 속성, 링커, 입력
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("fail\n");
		return -1;
	}

	char ipaddr[] = "230.200.12.5";
	printf("ip : %s\n", ipaddr);
	printf("ip : 0x%08X\n", inet_addr(ipaddr));
	IN_ADDR in_addr;
	in_addr.s_addr = inet_addr(ipaddr);
	printf("ip : %s\n", inet_ntoa(in_addr));

	unsigned short us = 0x1234;
	unsigned long ul = 0x12345678;

	unsigned short n_us = htons(us);
	unsigned long n_ul = htonl(ul);

	printf("0x%08X = 0x%08X\n", us, htons(us));
	printf("0x%08X = 0x%08X\n", ul, htonl(ul));
	printf("0x%08X = 0x%08X\n", n_us, ntohs(n_us));
	printf("0x%08X = 0x%08X\n", n_ul, ntohl(n_ul));
	

	printf("good\n");
	WSACleanup();

	return 0;
}