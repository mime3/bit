// CalculatorDLL.cpp : DLL의 초기화 루틴을 정의합니다.
//

#include "pch.h"
#include "framework.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int WINAPI Calculator(int num1, int num2, WCHAR oper)
{
	int result = 0;
	switch (oper)
	{
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	case '*':
		result = num1 * num2;
		break;
	case '/':
		if (num2 == 0)
		{
			AfxMessageBox(_T("num2 == 0"));
			break;
		}
		result = num1 / num2;
		break;
	default:
		break;
	}
	return result;
}
