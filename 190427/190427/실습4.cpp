#include "../../../2018/procademy/Lib/GDIColor.h"
#pragma comment(lib, "../../../2018/procademy/minLib/x64/Debug/MinLib.lib")

#include <windows.h>
#include <tchar.h>
#include "resource1.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//int APIENTRY _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_  LPTSTR cmdLine, _In_ int showCmd)
//{
//	HWND hWnd;
//	HWND hwnd;
//	MSG msg;
//	WNDCLASSEX wndClass;
//	g_hInst = hInst;
//
//	wndClass.cbClsExtra = 0; // 클래스 여유공간
//	wndClass.cbWndExtra = 0; // 윈도우 여유공간
//	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wndClass.hInstance = hInst;
//	wndClass.lpfnWndProc = WndProc;
//	wndClass.lpszClassName = lpszClass;
//	wndClass.lpszMenuName = NULL;
//	wndClass.style = CS_HREDRAW | CS_VREDRAW;
//	wndClass.hIconSm = 0; // ex에서 추가
//	wndClass.cbSize = sizeof(WNDCLASSEX); // 클래스크기
//	RegisterClassEx(&wndClass);
//
//	hWnd = CreateWindow(lpszClass, TEXT("hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//		NULL, NULL, hInst, NULL);
//
//	ShowWindow(hWnd, SW_SHOW);
//
//
//	while (1)
//	{
//		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT)
//				break;
//			//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//			{
//				TranslateMessage(&msg);
//				DispatchMessage(&msg);
//			}
//		}
//		else
//		{
//		}
//	}
//}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
	{
		HDC hdc = GetDC(hWnd);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_INITDIALOG: {	}
						return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL: EndDialog(hDlg, IDCANCEL);	return 0;
		}
		return TRUE;
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, PSTR lpCmdLine, int nShowCmd) 
{
	INT_PTR ret = DialogBox(hInst,	MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc);			
		// 부모 윈도우
		// Proc..
		// instance
		// 다이얼로그 선택
	return 0;
}
