#include "../../../2018/procademy/Lib/GDIColor.h"
#pragma comment(lib, "../../../2018/procademy/minLib/x64/Debug/MinLib.lib")

#include <windows.h>
#include <tchar.h>
#include "resource1.h"

#define IDC_BUTTON	1
#define IDC_EDIT	2
#define IDC_LISTBOX	3
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");
HWND hBtn, hEdit, hListBox;


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
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); // 메뉴 방법 1
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = 0; // ex에서 추가
	wndClass.cbSize = sizeof(WNDCLASSEX); // 클래스크기
	RegisterClassEx(&wndClass);

	// 메뉴 방법2
	HMENU menu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_MENU1));
	hWnd = CreateWindow(lpszClass, TEXT("hi"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);
	// 메뉴 방법3
	SetMenu(hWnd, menu);

	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			//if (!TranslateAccelerator(msg.hWnd, hAccelTable, &msg))
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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu = NULL;	// 메뉴 핸들 저장용
	static int submenu1 = ID_MENU1_TEST1;
	static int submenu2 = ID_MENU2_TEST4;

	switch (message)
	{
	case WM_CREATE:
	{
		hEdit = CreateWindow(TEXT("Edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 90, 20, hWnd, (HMENU)IDC_EDIT, 0, 0);
		hBtn = CreateWindow(TEXT("button"), TEXT("Push"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 40, 90, 20, hWnd, (HMENU)IDC_BUTTON, 0, 0);
		hListBox = CreateWindow(TEXT("listbox"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			150, 10, 90, 90, hWnd, (HMENU)IDC_LISTBOX, 0, 0);

		SendMessage(hEdit, EM_LIMITTEXT, 5, 0);
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("AAAA"));
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("BBBB"));
		return 0;
	}
	case WM_LBUTTONDOWN:
	{

		//if (hMenu == NULL)
		//{
		//	// 윈도우 메뉴의 핸들 얻기 
		//	hMenu = GetMenu(hWnd);
		//	// 윈도우의 메뉴 부착, 0이므로 메뉴가 소멸됨..
		//	SetMenu(hWnd, NULL);
		//}
		//else
		//{
		//	// 윈도우의 메뉴 부착
		//	HMENU temp = GetMenu(hWnd);
		//	SetMenu(hWnd, hMenu);
		//	// 부착하면 저장용 변수 0 초기화
		//	hMenu = NULL;
		//}
		HMENU h = GetMenu(hWnd);
		// 메뉴를 추가... 어디에 추가되는가??
		AppendMenu(h, MF_POPUP, 5000, TEXT("추가메뉴"));	// 5000 ==> ID값..
		HMENU h1 = GetSubMenu(h, 0);
		AppendMenu(h1, MF_STRING, 5001, TEXT("BBB")); // 메뉴 항목이 텍스트 문자열임을 지정합니다.lpNewItem의 매개 변수는 문자열에 대한 포인터입니다.
		AppendMenu(h1, MF_SEPARATOR, 5002, TEXT("")); // MF_SEPARATOR :: lpNewItem 및 uIDNewItem 매개 변수는 무시됩니다.
		// 메뉴바에 직접 추가한 경우에는 반드시 메뉴바를 다시 그려야 한다.
		DrawMenuBar(hWnd);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		HMENU  h = GetMenu(hWnd);
		HMENU hSub = GetSubMenu(h, 0);
		RemoveMenu(h, 5000, MF_BYCOMMAND);
		RemoveMenu(hSub, ID_MENU1_TEST2, MF_BYCOMMAND);
		RemoveMenu(hSub, 5001, MF_BYCOMMAND);
		RemoveMenu(hSub, 5002, MF_BYCOMMAND);
		DrawMenuBar(hWnd);
		return 0;
	}
	case WM_INITMENUPOPUP:
	{
		HMENU hMenu = (HMENU)wParam;
		CheckMenuItem(hMenu, ID_MENU1_TEST1,
			submenu1 == ID_MENU1_TEST1 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST2,
			submenu1 == ID_MENU1_TEST2 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST3,
			submenu1 == ID_MENU1_TEST3 ? MF_CHECKED : MF_UNCHECKED);

		EnableMenuItem(hMenu, ID_MENU1_TEST1,
			submenu1 == ID_MENU1_TEST1 ? MF_CHECKED | MF_DISABLED : MF_ENABLED);

		EnableMenuItem(hMenu, ID_MENU2_TEST4,
			submenu2 == ID_MENU2_TEST4 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST5,
			submenu2 == ID_MENU2_TEST5 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST6,
			submenu2 == ID_MENU2_TEST6 ? MF_GRAYED : MF_ENABLED);
	}
	return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))		// ID 조사
		{
		case ID_MENU1_TEST1:	
			SetWindowText(hWnd, TEXT("ID_MENU1_TEST1"));
			submenu1 = ID_MENU1_TEST1;
			break;
		case ID_MENU1_TEST2:	
			SetWindowText(hWnd, TEXT("ID_MENU1_TEST2"));
			submenu1 = ID_MENU1_TEST2;
			break;
		case ID_MENU1_TEST3:	
			SetWindowText(hWnd, TEXT("ID_MENU1_TEST3"));
			submenu1 = ID_MENU1_TEST3;
			break;
		case ID_MENU2_TEST4:	
			SetWindowText(hWnd, TEXT("ID_MENU2_TEST4"));
			submenu2 = ID_MENU2_TEST4;
			break;
		case ID_MENU2_TEST5:	
			SetWindowText(hWnd, TEXT("ID_MENU2_TEST5"));
			submenu2 = ID_MENU2_TEST5;
			break;
		case ID_MENU2_TEST6:	
			SetWindowText(hWnd, TEXT("ID_MENU2_TEST6"));
			submenu2 = ID_MENU2_TEST6;
			break;
		case IDC_EDIT:
			if(HIWORD(wParam) == EN_CHANGE)
			{
				TCHAR tempBuffer[256];
				GetWindowText(hEdit, tempBuffer, 256);
				SetWindowText(hWnd, tempBuffer);
			}
			break;
		case IDC_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED)
			{
				TCHAR tempBuffer[256];
				GetWindowText(hEdit, tempBuffer, sizeof(tempBuffer));
				SendMessage(hListBox, LB_ADDSTRING, NULL, (LPARAM)tempBuffer);
			}
			break;
		}
	}
	case WM_CONTEXTMENU:
	{
		return 0;
		HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
		HMENU hSubMenu = GetSubMenu(hMenu, 1);
		POINT  pt = { LOWORD(lParam), HIWORD(lParam) };
		// 스크린 좌표...
		TrackPopupMenu(hSubMenu, TPM_LEFTBUTTON, pt.x, pt.y, 0, hWnd, 0);
		return 0;
	}
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