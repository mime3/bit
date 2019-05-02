// AsyncSelect.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "AsyncSelect.h"
#pragma comment(lib, "ws2_32.lib") // 프로젝트 속성, 링커, 입력
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h>
#include <WinSock2.h>
#include <stdio.h>

#define MAX_LOADSTRING 100
#define UM_SOCKET (WM_USER + 100)

#define BUFFERSIZE	1024
#define PORT	40100

struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFFERSIZE];
	int recvBytes;
	int sendBytes;
	BOOL recvDelayed;
};

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd;
SOCKET listenSock;
int nTotalSockets = 0;
SOCKETINFO* SocketInfoArray[FD_SETSIZE];

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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

	//u_long on = 1;
	//retval = ioctlsocket(listenSock, FIONBIO, &on);
	retval = WSAAsyncSelect(listenSock, hWnd, UM_SOCKET, FD_ACCEPT | FD_CLOSE);
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
	getpeername(ptr->sock, (SOCKADDR*)& clientAddr, &addrLen);
	printf("클라이언트 종료 : IP = %s, PORT = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	closesocket(ptr->sock);
	delete ptr;

	for (int i = nIndex; i < nTotalSockets; i++)
	{
		SocketInfoArray[i] = SocketInfoArray[i + 1];
	}
	nTotalSockets--;
}

int GetSocketInfo(SOCKET sock)
{
	for (int i = 0; i < nTotalSockets; ++i)
	{
		if (SocketInfoArray[i]->sock == sock)
			return i;
	}
	return -1;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASYNCSELECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

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

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASYNCSELECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	WSACleanup();
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASYNCSELECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASYNCSELECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
	case UM_SOCKET:
	{
		SOCKETINFO* ptr;
		SOCKET clientSock;
		SOCKADDR_IN clientAddr;
		int addrLen;
		int retval;

		if (WSAGETSELECTERROR(lParam))
		{
			RemoveSocketInfo(GetSocketInfo(wParam));
			break;
		}

		switch (WSAGETSELECTEVENT(lParam))
		{
		case FD_ACCEPT:
			addrLen = sizeof(clientAddr);
			clientSock = accept(wParam, (SOCKADDR*)& clientAddr, &addrLen);
			if (clientSock == INVALID_SOCKET)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					DisplayMessage();
				break;
			}
			printf("[SERVER] Connect Client : IP = %s, PORT = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
			AddSocketInfo(clientSock);
			retval = WSAAsyncSelect(clientSock, hWnd, UM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
			if (retval == SOCKET_ERROR)
			{
				DisplayMessage();
				RemoveSocketInfo(GetSocketInfo(clientSock));
			}
			break;
		case FD_READ:
			ptr = SocketInfoArray[GetSocketInfo(wParam)];
			if (ptr->recvBytes > 0)
			{
				ptr->recvDelayed = TRUE;
				break;
			}
			retval = recv(ptr->sock, ptr->buf, BUFFERSIZE, 0);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					DisplayMessage();
					RemoveSocketInfo(GetSocketInfo(wParam));
				}
				break;
			}
			ptr->recvBytes = retval;

			ptr->buf[retval] = 0;
			addrLen = sizeof(clientAddr);
			getpeername(ptr->sock, (SOCKADDR*)& clientAddr, &addrLen);
			printf("[SERVER] IP = %s, PORT = %d, MESSAGE = %s\n",
				inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port),
				ptr->buf);
			//break;
		case FD_WRITE:
			ptr = SocketInfoArray[GetSocketInfo(wParam)];
			if (ptr->recvBytes <= ptr->sendBytes)
				break;

			retval = send(ptr->sock, ptr->buf + ptr->sendBytes, ptr->recvBytes - ptr->sendBytes, 0);
			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					DisplayMessage();
					RemoveSocketInfo(wParam);
				}
				break;
			}
			ptr->sendBytes += retval;
			if (ptr->recvBytes == ptr->sendBytes)
			{
				ptr->recvBytes = ptr->sendBytes = 0;
				if (ptr->recvDelayed)
				{
					ptr->recvDelayed = FALSE;
					PostMessage(hWnd, UM_SOCKET, wParam, FD_READ);
				}
			}
			break;
		case FD_CLOSE:
			RemoveSocketInfo(GetSocketInfo(wParam));
			break;
		}


		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
