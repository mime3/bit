#include <Windows.h>
#include <stdio.h>
#define UM_TEST WM_USER + 1

int main()
{
	HWND hwnd = FindWindow("First", NULL);

	bool ret = PostMessage(hwnd, UM_TEST, 10, 50);
	if (ret)
	{
		printf("���� �Ϸ�\n");
	}
	printf("����\n");
	getchar();
	return 0;
}