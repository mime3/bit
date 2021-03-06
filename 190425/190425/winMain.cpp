#include "../../../2018/procademy/Lib/GDIColor.h"
#pragma comment(lib, "../../../2018/procademy/minLib/x64/Debug/MinLib.lib")

#include <windowsx.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include "resource.h"

#define MBox(x) MessageBox( 0, x, TEXT(""), MB_OK)
#define IsKeyPress(vk) ( GetKeyState(vk) & 0xFF00)
#define IsKeyToggle(vk) ( GetKeyState(vk) & 0x00FF)
static HCURSOR h1 = LoadCursorFromFile(TEXT("C:\\windows\\cursors\\size1_i.cur"));
static HCURSOR h2 = LoadCursorFromFile(TEXT("C:\\windows\\cursors\\size1_il.cur"));


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

int APIENTRY _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrev, _In_  LPTSTR cmdLine, _In_ int showCmd)
{
	HWND hWnd;
	//HWND hwnd;
	MSG msg;
	WNDCLASSEX wndClass;
	g_hInst = hInst;

	wndClass.cbClsExtra = 0; // 클래스 여유공간
	wndClass.cbWndExtra = 0; // 윈도우 여유공간
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
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


    while(1)
    {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
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
			Sleep(1);
		}
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	static BOOL bNowDraw = FALSE;
	static POINTS pt = { 100, 100 };
	HDC	hdcDisplay;
	static int	cxClient, cyClient;
	static RECT rc = { 100, 100, 300 ,300 };


	switch (message)
	{
	case WM_CREATE:
		setlocale(LC_ALL, "");
		break;
	case WM_MOVE:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_ERASEBKGND:
		return TRUE;
		break;
	case WM_PAINT:
	{
		//TCHAR str[] = TEXT("네 번째 인수는 출력할 영역을 담고 있는 구조체 포인터이다.다섯번째 인수는 DrawText 함수가 문자열을 출력할 방법을지정하는 플래그이며 다음과 같은 여러 가지 플래그의 조합을 지정한다.");
		////TCHAR str2[] = TEXT("TEXT 텍스트");
		//RECT rt = { 100,100,400,300 };

		hdcDisplay = CreateDC(TEXT("DISPLAY"), 0, 0, 0);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		//SetTextAlign(hdc, TA_CENTER);
		//TextOut(hdc, 200, 60, TEXT("Buautiful Korea"), 15);
		//TextOut(hdc, 200, 80, TEXT("is My"), 5);
		//TextOut(hdc, 200, 100, TEXT("Lovely Home Country"), 19);

		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);

		//SetPixel(hdc, 10, 10, RGB(255, 0, 0));
		//MoveToEx(hdc, 50, 50, NULL);
		//LineTo(hdc, 300, 90);
		//Rectangle(hdc, 50, 100, 200, 180);
		//Ellipse(hdc, 220, 100, 400, 200);

		//HBRUSH brush = (HBRUSH)GetStockObject(GRAY_BRUSH);
		//HBRUSH old = (HBRUSH)SelectObject(hdc, BRUSH(13));
		//Rectangle(hdc, 10, 10, 100, 100);
		//SelectObject(hdc, old);

		//HPEN pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		//Rectangle(hdc, 10, 10, 100, 100);
		//DeleteObject(SelectObject(hdc, oldPen));

		//Rectangle(hdc, 100, 100, 200, 200);
		//// 논리 1= 0.1mm(물리),  y축 증가 위 )
		//SetMapMode(hdc, MM_HIMETRIC);
		//HBRUSH old = (HBRUSH)SelectObject(hdc, BRUSH(13));
		//Rectangle(hdc, 0, 0, 100, -100);

		BitBlt(hdc, 0, 0, cxClient, cyClient, hdcDisplay, 0, 0, SRCCOPY);

		DeleteDC(hdcDisplay);
		TextOut(hdc, pt.x, pt.y, TEXT("#"), 1);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_MOUSEMOVE:
	{
		//if (bNowDraw)
		//{
		//	HDC hdc = GetDC(hWnd);
		//	SetROP2(hdc, R2_NOT);
		//	MoveToEx(hdc, start.x, start.y, NULL);
		//	LineTo(hdc, end.x, end.y);
		//	end = MAKEPOINTS(lParam);
		//	MoveToEx(hdc, start.x, start.y, NULL);
		//	LineTo(hdc, end.x, end.y);
		//	ReleaseDC(hWnd, hdc);
		//}
		//if (GetCapture() == hWnd)   // 캡쳐중일때만..
		//{
		//	POINTS pt = MAKEPOINTS(lParam);
		//	HDC hdc = GetDC(hWnd);
		//	SetROP2(hdc, R2_NOTXORPEN); // 그리기 모드 변경
		//	SelectObject(hdc, PEN(7));
		//	SelectObject(hdc, GetStockObject(NULL_PEN));
		//	SelectObject(hdc, BRUSH(10));
		//	//SelectObject(hdc, GetStockObject(NULL_BRUSH));
		//	Rectangle(hdc, start.x, start.y, end.x, end.y);
		//	Rectangle(hdc, start.x, start.y, pt.x, pt.y);
		//	end = pt; // 현재 점을 Old에 보관
		//	ReleaseDC(hWnd, hdc);
		//}
		if (GetCapture() == hWnd)   // 캡쳐중일때만..
		{
			POINT pt;
			GetCursorPos(&pt);
			hdcDisplay = CreateDC(TEXT("DISPLAY"), 0, 0, 0);
			HDC hdc = GetDC(hWnd);
			StretchBlt(hdc, 0, 0, cxClient, cyClient,
				hdcDisplay, pt.x, pt.y, 100, 100,
				SRCCOPY);
			DeleteDC(hdcDisplay);
			ReleaseDC(hWnd, hdc);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hWnd);
		//SetTextAlign(hdc, TA_UPDATECP);
		//TextOut(hdc, 200, 200, TEXT("Buautiful Korea"), 15);
		//TextOut(hdc, 200, 220, TEXT("is My"), 5);
		//TextOut(hdc, 200, 240, TEXT("Lovely Home Country"), 19);
		
		//start = MAKEPOINTS(lParam);
		//end = start;
		//bNowDraw = TRUE;

		//start = end = MAKEPOINTS(lParam);
		SetCapture(hWnd);

		//BOOL bPresent = GetSystemMetrics(SM_MOUSEPRESENT);
		//BOOL bWheel = GetSystemMetrics(SM_MOUSEWHEELPRESENT);
		//int	 nBtn = GetSystemMetrics(SM_CMOUSEBUTTONS);
		//int scx = GetSystemMetrics(SM_CXSCREEN);
		//int scy = GetSystemMetrics(SM_CYSCREEN);
		//TCHAR info[128];
		//wsprintf(info, _TEXT("%s %s is installed. (%d Buttons)\n"),
		//	(bWheel ? _TEXT("Wheel") : _TEXT("")), (bPresent ? _TEXT("Mouse") : _TEXT("No Mouse")), nBtn);
		//TCHAR temp[64];
		//wsprintf(temp, _TEXT("\nScreen Resolution : %d * %d"), scx, scy);
		//_tcscat_s(info, 128, temp);
		//MessageBox(NULL, info, TEXT(""), MB_OK);

		POINTS pt = MAKEPOINTS(lParam);
		POINT pt1 = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		TCHAR buf[50];
		wsprintf(buf, TEXT("(%d:%d)\r\n(%d:%d)"), pt.x, pt.y, pt1.x, pt1.y);
		//MessageBox(NULL, buf, TEXT(""), MB_OK);

		HDC memDC = CreateCompatibleDC(hdc);
		// 리소스에서 로드할때만 사용
		HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));

		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);
		// 메모리 DC에 비트맵 선택
		SelectObject(memDC, hBitmap);
		// 비트맵으로출력
		TextOut(memDC, 5, 5, TEXT("LoadBitmap으로 출력"), 15);
		HICON icon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
		DrawIcon(memDC, 10, 10, icon);
		// 메모리 DC --> 화면 DC//
		BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
		// 메모리 제거
		DeleteDC(memDC);
		DeleteObject(hBitmap);


		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_LBUTTONUP:
	{
		//bNowDraw = FALSE;
		HDC hdc = GetDC(hWnd);
		//MoveToEx(hdc, start.x, start.y, NULL);
		//LineTo(hdc, end.x, end.y);

		if (GetCapture() == hWnd)
		{
			ReleaseCapture();
			//	// 최종선은 R2_COPYPEN으로 그려야 한다.
			//	//HDC hdc = GetDC(hWnd); // 디폴트 그리기 모드가 R2_COPYPEN 이다.		
			//	SelectObject(hdc, GetStockObject(NULL_BRUSH));
			//	SelectObject(hdc, PEN(7));
			//	//SelectObject(hdc, GetStockObject(NULL_PEN));
			//	Rectangle(hdc, start.x, start.y, end.x, end.y);
			//	//ReleaseDC(hWnd, hdc);
		}

		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		if (wParam & MK_SHIFT)
		{
			MessageBox(NULL, TEXT("RBUTTON+SHIFT"), TEXT(""), MB_OK);
		}
		else if (wParam & MK_CONTROL)
		{
			MessageBox(NULL, TEXT("RBUTTON+CONTROL"), TEXT(""), MB_OK);
		}
		

		HDC hdc = GetDC(hWnd);
		// 화면 DC와 호환(동일색상)되는 메모리 DC를 얻음..
		HDC memDC = CreateCompatibleDC(hdc);

		HBITMAP hBitmap = (HBITMAP)LoadImage(0, TEXT("pointillist.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		// 커서, Icon load시만 사용
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);
		// 메모리 DC에 비트맵 선택
		SelectObject(memDC, hBitmap);
		// 비트맵으로출력
		TextOut(memDC, 5, 5, TEXT("LoadImage로 출력"), 13);
		// 메모리 DC --> 화면 DC//
		POINTS pt = MAKEPOINTS(lParam);
		BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
		// 메모리 제거
		DeleteDC(memDC);
		ReleaseDC(hWnd, hdc);
		DeleteObject(hBitmap);

		break;
	}
	case WM_NCHITTEST:
	{
		DWORD code = DefWindowProc(hWnd, message, wParam, lParam);
		if (code == HTCLIENT && GetKeyState(VK_CONTROL) < 0)
			code = HTCAPTION;
		if (code == HTLEFT)    
			code = HTRIGHT;
		return code;
	}
	case WM_KEYDOWN: 
	{
		if (wParam == VK_F1 && IsKeyPress(VK_CONTROL))
		{
			MBox(TEXT("CTRL + F1"));
		}
		else if (wParam == VK_F1 && IsKeyToggle(VK_CAPITAL))
		{
			MBox(TEXT("CAPSLOCK + F1"));
		}

		

		switch (wParam) 
		{
		case VK_LEFT: pt.x -= 10; 
			break;
		case VK_RIGHT:pt.x += 10; 
			break;
		case VK_UP:   pt.y -= 10; 
			break;
		case VK_DOWN: pt.y += 10; 
			break;
		default:
			break;
		}
		HDC hdc = GetDC(hWnd);
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_SETCURSOR:
	{
		int code = LOWORD(lParam);
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		if (code == HTCLIENT && PtInRect(&rc, pt))
		{
			SetCursor(LoadCursor(0, IDC_ARROW));
			return TRUE;
		}
		if (code == HTLEFT || code == HTRIGHT)
		{
			SetCursor(h2);
			return TRUE; // 커서를 변경한 경우 TRUE 리턴
		}
		else if (code == HTTOP || code == HTBOTTOM)
		{
			SetCursor(h1);
			return TRUE;
		}

		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
