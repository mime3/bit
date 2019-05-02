#include "../../../2018/procademy/Lib/GDIColor.h"
#pragma comment(lib, "../../../2018/procademy/minLib/x64/Debug/MinLib.lib")

#include <Windows.h>
#include <tchar.h>
#include "resource1.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")


HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_  LPTSTR cmdLine, _In_ int showCmd)
{
	HWND hWnd;
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wndClass;
	g_hInst = hInst;

	wndClass.cbClsExtra = 0; // 클래스 여유공간
	wndClass.cbWndExtra = 0; // 윈도우 여유공간
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = 0; // ex에서 추가
	wndClass.cbSize = sizeof(WNDCLASSEX); // 클래스크기
	RegisterClassEx(&wndClass);

	hWnd = CreateWindow(lpszClass, TEXT("hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);


	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
		}
	}
}


//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_CREATE:
//		break;
//	case WM_PAINT:
//	{
//		HDC hdc = GetDC(hWnd);
//		ReleaseDC(hWnd, hdc);
//		break;
//	}
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//	}
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}


WNDPROC old; // 원래의 EditBox의 메세지 처리함수의 주소를 담을 변수
LRESULT CALLBACK foo(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CHAR:
		if ((wParam >= '0' && wParam <= '9') || wParam == 8)
			return CallWindowProc(old, hwnd, msg, wParam, lParam);
		return 0; // 숫자 이외의 경우는 무시한다.
	}
	// 나머지 모든 메세지는 원래의 함수로 전달한다.
	return CallWindowProc(old, hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	static HINSTANCE hInst;
	static HWND hProgress;
	static int	Pos = 10;

	switch (msg)
	{
	case WM_CREATE:	hEdit = CreateWindow(TEXT("edit"), TEXT(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 200, 200, hwnd, (HMENU)1, 0, 0);
		old = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)foo);
		SetFocus(hEdit);

		INITCOMMONCONTROLSEX ex;
		ex.dwSize = sizeof(ex);
		ex.dwICC = ICC_PROGRESS_CLASS;
		InitCommonControlsEx(&ex);
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		hProgress = CreateWindow(TEXT("msctls_progress32"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
			10, 10, 300, 20, hwnd, (HMENU)1, hInst, 0);
		// 컨트롤 초기화
		SendMessage(hProgress, PBM_SETRANGE32, 0, 100);
		SendMessage(hProgress, PBM_SETPOS, 10, 0);
		return 0;
	case WM_LBUTTONDOWN:
		Pos += 10;
		SendMessage(hProgress, PBM_SETPOS, Pos, 0);
		return 0;
	case WM_RBUTTONDOWN:
		Pos -= 10;
		SendMessage(hProgress, PBM_SETPOS, Pos, 0);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
