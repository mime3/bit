#include "../../../2018/procademy/Lib/GDIColor.h"
#pragma comment(lib, "../../../2018/procademy/minLib/x64/Debug/MinLib.lib")

#include <Windows.h>
#include <tchar.h>
#include "resource1.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")


HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_  LPTSTR cmdLine, _In_ int showCmd)
{
	HWND hWnd;
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

typedef struct tagDATA {
	TCHAR str[20];
	int   num;
}DATA;
BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	static DATA* pData;
	switch (msg)
	{
		// Dialog가 처음 나타날때 발생. 각 콘트롤을 초기화 한다.
	case WM_INITDIALOG: 
	{
		pData = (DATA*)lParam;
		SetDlgItemText(hDlg, IDC_EDIT1, pData->str);
		SetDlgItemInt(hDlg, IDC_EDIT2, pData->num, 0);
	}
						break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDIT1, pData->str, sizeof(pData->str));
			pData->num = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
	}
	return FALSE; // 메세지 처리를 안한경우..
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DATA  data = { TEXT("홍길동"), 20 };
		INT_PTR ret = DialogBoxParam(GetModuleHandle(0),// hinstance
			MAKEINTRESOURCE(IDD_DIALOG1),
			hwnd,		// 부모
			(DLGPROC)DlgProc, // 메세지 함수.
			(LPARAM)& data); // WM_INITDIALOG의 lParam로 전달된다.
		if (ret == IDOK)
		{
			// 이제 Dialog에 입력한 값은 data에 있다.
			TCHAR buf[128];
			wsprintf(buf, TEXT("%s / %d"), data.str, data.num);
			SetWindowText(hwnd, buf);
		}
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}