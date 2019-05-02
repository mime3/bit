#include "../../../2018/procademy/Lib/GDIColor.h"
#pragma comment(lib, "../../../2018/procademy/minLib/x64/Debug/MinLib.lib")
#include <windows.h>
#include <tchar.h>
#define UM_TEST WM_USER + 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

BOOL fun_ModifyStylpe(HWND hwnd, LONG_PTR Add, LONG_PTR Remove, BOOL bRedraw)
{
	BOOL  bFlag = FALSE;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	style |= Add;
	style &= ~Remove;
	bFlag = (BOOL)SetWindowLongPtr(hwnd, GWL_STYLE, style);
	if (bFlag && bRedraw)
		SetWindowPos(hwnd, 0, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
	return bFlag;
}


int APIENTRY _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_  LPTSTR cmdLine, _In_ int showCmd)
{
	HWND hWnd;
	HWND hwnd;
	MSG message;
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

	//hWnd = FindWindow(TEXT("Shell_TrayWnd"), 0);
	//if (IsWindowVisible(hWnd))
	//	ShowWindow(hWnd, SW_HIDE);
	//else
	//	ShowWindow(hWnd, SW_SHOW);
	//return 0;



	//hwnd = FindWindow(0, _TEXT("계산기"));
	//if (hwnd == 0) {
	//	MessageBox(0, _TEXT("계산기 핸들을 얻을 수 없습니다."),
	//		_TEXT("알림"), MB_OK | MB_ICONERROR);
	//	return 0;
	//}
	//else {
	//	TCHAR temp[20];
	//	wsprintf(temp, _TEXT("계산기 핸들 : %d"), (int)hwnd);
	//	MessageBox(0, temp, _TEXT("알림"), MB_OK);

	//	TCHAR name[60];
	//	RECT rcCalc;
	//	GetClassName(hwnd, name, sizeof(name));
	//	GetWindowRect(hwnd, &rcCalc);

	//	TCHAR info[256];
	//	wsprintf(info, _TEXT("클래스 명 : %s\n위치 : %d,%d ~ %d,%d"), name,
	//		rcCalc.left, rcCalc.top, rcCalc.right, rcCalc.bottom);
	//	MessageBox(0, info, TEXT("계산기 정보"), MB_OK);

	//	//계산기 이동하기
	//	MoveWindow(hwnd, 10, 10, rcCalc.right - rcCalc.left, rcCalc.bottom - rcCalc.top, TRUE);

	//	//계산기 숨기기
	//	MessageBox(0, _TEXT("계산기"), TEXT("계산기 숨기기"), MB_OK);
	//	ShowWindow(hwnd, SW_HIDE);

	//	//계산기 보이기
	//	MessageBox(0, _TEXT("계산기"), TEXT("계산기 보이기"), MB_OK);
	//	ShowWindow(hwnd, SW_SHOW);

	//	//계산기 종료하기
	//	MessageBox(0, _TEXT("계산기"), TEXT("계산기 종료하기"), MB_OK);
	//	SendMessage(hwnd, WM_CLOSE, 0, 0);


	//}
	//return 0;


	hWnd = CreateWindow(lpszClass, TEXT("hi"), WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);

	//실시간 클래스 정보 수정
	MessageBox(0, TEXT("실시간 정보 수정"), TEXT("First"), MB_OK);
	//SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)GetStockObject(DKGRAY_BRUSH));
	SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)GDIColor::GetInstance()->_brush[10]);
	InvalidateRect(hWnd, NULL, TRUE);
	MessageBox(0, TEXT("Hello,API"), TEXT("First"), MB_OK);

	//실시간 클래스 정보 획득
	TCHAR temp[126];
	DWORD flag = (DWORD)GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND);
	wsprintf(temp, _TEXT("R : %d, G : %d : B : %d"), GetRValue(flag), GetGValue(flag), GetBValue(flag));
	MessageBox(0, temp, TEXT("획득정보"), MB_OK);

	hWnd = FindWindow(NULL, _TEXT("제목 없음 - 그림판"));
	fun_ModifyStylpe(hWnd, WS_THICKFRAME, WS_SYSMENU, TRUE);
	MessageBox(0, TEXT(""), TEXT(""), MB_OK);
	fun_ModifyStylpe(hWnd, WS_SYSMENU, WS_THICKFRAME, TRUE);
	MessageBox(0, TEXT(""), TEXT(""), MB_OK);

	//PostQuitMessage(0);

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, BRUSH(7));
		SelectObject(hdc, PEN(5));
		Rectangle(hdc, 10, 10, 100, 100);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		RECT rect;
		GetClientRect(hWnd, &rect);
		PatBlt(hdc, 0, 0, rect.right, rect.bottom, WHITENESS);
		SelectObject(hdc, BRUSH(6));
		SelectObject(hdc, PEN(12));
		Rectangle(hdc, 120, 10, 210, 100);
		SelectObject(hdc, GetStockObject(WHITE_BRUSH));
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		RECT rect = { 119, 9, 210, 100 };
		RECT rect2 = { 0, 0, 100, 100 };
		InvalidateRect(hWnd, &rect, TRUE);
		InvalidateRect(hWnd, &rect2, TRUE);
		break;
	}
	case WM_RBUTTONDOWN:
		SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case UM_TEST:
		TCHAR buffer[128];
		wsprintf(buffer, TEXT("%d+%d=%d"), (int)wParam, (int)lParam, (int)(wParam + lParam));
		MessageBox(hWnd, buffer, TEXT("gg"), MB_OK);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
