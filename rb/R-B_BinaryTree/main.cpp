// main.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	RB_BinaryTree rb;
	rb.Insert(1);
	rb.Insert(2);
	rb.Insert(3);
	rb.Insert(4);
	rb.Insert(5);
	rb.Insert(6);
	rb.Insert(7);
	rb.Insert(8);
	rb.Insert(9);
	rb.Insert(10);
	rb.Delete(1);
	rb.Delete(9);
	rb.Delete(8);
	system("pause");
    return 0;
}

