#include <Windows.h>
#include <stdio.h>
#define UM_TEST WM_USER + 1

int main()
{
	HWND hwnd = FindWindow("First", NULL);

	bool ret = PostMessage(hwnd, UM_TEST, 10, 50);
	if (ret)
	{
		printf("전송 완료\n");
	}
	printf("종료\n");
	getchar();
	return 0;
}