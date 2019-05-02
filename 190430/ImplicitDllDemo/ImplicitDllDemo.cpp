// ImplicitDllDemo.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*__declspec(dllexport)*/ BOOL WINAPI GetModulePath(CString& strPath)
{
	TCHAR szBuffer[MAX_PATH];
	ZeroMemory(szBuffer, sizeof(szBuffer));
	GetModuleFileName(NULL, szBuffer, MAX_PATH);

	for (int i = lstrlen(szBuffer) - 1; i >= 0; --i)
	{
		if (szBuffer[i] == '\\')
		{
			int j = lstrlen(szBuffer) - 1;
			for (; j >= i; --j)
			{
				szBuffer[j] = NULL;
			}

			if (szBuffer[j] == ':')
				szBuffer[j + 1] = '\\';

			strPath = szBuffer;
			return TRUE;
		}
	}
	return FALSE;
}