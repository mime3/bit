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

	wndClass.cbClsExtra = 0; // Ŭ���� ��������
	wndClass.cbWndExtra = 0; // ������ ��������
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = 0; // ex���� �߰�
	wndClass.cbSize = sizeof(WNDCLASSEX); // Ŭ����ũ��
	RegisterClassEx(&wndClass);

	//hWnd = FindWindow(TEXT("Shell_TrayWnd"), 0);
	//if (IsWindowVisible(hWnd))
	//	ShowWindow(hWnd, SW_HIDE);
	//else
	//	ShowWindow(hWnd, SW_SHOW);
	//return 0;



	//hwnd = FindWindow(0, _TEXT("����"));
	//if (hwnd == 0) {
	//	MessageBox(0, _TEXT("���� �ڵ��� ���� �� �����ϴ�."),
	//		_TEXT("�˸�"), MB_OK | MB_ICONERROR);
	//	return 0;
	//}
	//else {
	//	TCHAR temp[20];
	//	wsprintf(temp, _TEXT("���� �ڵ� : %d"), (int)hwnd);
	//	MessageBox(0, temp, _TEXT("�˸�"), MB_OK);

	//	TCHAR name[60];
	//	RECT rcCalc;
	//	GetClassName(hwnd, name, sizeof(name));
	//	GetWindowRect(hwnd, &rcCalc);

	//	TCHAR info[256];
	//	wsprintf(info, _TEXT("Ŭ���� �� : %s\n��ġ : %d,%d ~ %d,%d"), name,
	//		rcCalc.left, rcCalc.top, rcCalc.right, rcCalc.bottom);
	//	MessageBox(0, info, TEXT("���� ����"), MB_OK);

	//	//���� �̵��ϱ�
	//	MoveWindow(hwnd, 10, 10, rcCalc.right - rcCalc.left, rcCalc.bottom - rcCalc.top, TRUE);

	//	//���� �����
	//	MessageBox(0, _TEXT("����"), TEXT("���� �����"), MB_OK);
	//	ShowWindow(hwnd, SW_HIDE);

	//	//���� ���̱�
	//	MessageBox(0, _TEXT("����"), TEXT("���� ���̱�"), MB_OK);
	//	ShowWindow(hwnd, SW_SHOW);

	//	//���� �����ϱ�
	//	MessageBox(0, _TEXT("����"), TEXT("���� �����ϱ�"), MB_OK);
	//	SendMessage(hwnd, WM_CLOSE, 0, 0);


	//}
	//return 0;


	hWnd = CreateWindow(lpszClass, TEXT("hi"), WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);

	//�ǽð� Ŭ���� ���� ����
	MessageBox(0, TEXT("�ǽð� ���� ����"), TEXT("First"), MB_OK);
	//SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)GetStockObject(DKGRAY_BRUSH));
	SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)GDIColor::GetInstance()->_brush[10]);
	InvalidateRect(hWnd, NULL, TRUE);
	MessageBox(0, TEXT("Hello,API"), TEXT("First"), MB_OK);

	//�ǽð� Ŭ���� ���� ȹ��
	TCHAR temp[126];
	DWORD flag = (DWORD)GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND);
	wsprintf(temp, _TEXT("R : %d, G : %d : B : %d"), GetRValue(flag), GetGValue(flag), GetBValue(flag));
	MessageBox(0, temp, TEXT("ȹ������"), MB_OK);

	hWnd = FindWindow(NULL, _TEXT("���� ���� - �׸���"));
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
