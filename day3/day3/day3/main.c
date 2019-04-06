#include <stdio.h>
#include <windows.h>
#pragma warning(disable:4996)
// �迭 �ѱ��
void check(int * p, int size)
{
	// size�� �Ѱܾ� ��������
}

// k�� ���ö����� ��� -> puts
void put_a(char * string)
{
	while (*string)
	{
		putchar(*string++);
	}
	putchar('\n');
}

void mystrcpy(char * dst, char * src)
{
	memcpy(dst, src, strlen(src) + 1);
	//while (*dst++ = *src++);
}

void mystrcat(char * dst, const char * src)
{
	int len = strlen(dst);
	memcpy(dst + len, src, strlen(src) + 1);

	//while (*++dst);
	//while (*dst++ = *src++);
}

void intconnect(int * a, int ** p)
{
	*p = a;
}

void swap1(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap2(int **a, int **b)
{
	int temp = **a;
	**a = **b;
	**b = temp;
}

void swap3(int ***a, int ***b)
{
	int temp = ***a;
	***a = ***b;
	***b = temp;
}

void swap4(int **a, int **b)
{
	int *temp = *a;
	*a = *b;
	*b = temp;
}

void swap5(int ***a, int ***b)
{
	int *temp = **a;
	**a = **b;
	**b = temp;
}

void swap6(int ***a, int ***b)
{
	int **temp = *a;
	*a = *b;
	*b = temp;
}

void last(int * ka)
{
	*ka = 300;
}

void middle(int * pa)
{
	*pa = 200;
	last(pa);
}

void get_num(int(*p)[3])
{
	int rx, cx;
	for (rx = 0; rx < 2; rx++)
	{
		for (cx = 0; cx < 3; cx++)
			scanf("%d", &p[rx][cx]);
	}
}

void put_num(int(*p)[3])
{
	int rx, cx;
	for (rx = 0; rx < 2; rx++)
	{
		for (cx = 0; cx < 3; cx++)
			printf("%d ", p[rx][cx]); //(*(p+rx))[cx] , *(p[rx]+cx), *(*(p+rx)+cx)
	}
}

char * g = "abc";

/*Idea
���ڿ� ������
������ ���ڿ��� ������ ������ �����Ҵ� ��
���������� �ں��� �о �ѱ��ھ� �����ѵ�
�������۸� ���� ���ۿ� ������
*/ 
void mystrrev(char * buffer, int size)
{
	// �������� ���� �Ҵ�
	char * tempbuffer = (char *)malloc(size);
	// �ѱ��ھ� ����� ���� �����Ͱ� �̵��ϱ⋚���� temp�� �����ϰ� ������ �����͸� ���� ����
	char * movepointer = tempbuffer;
	// ���� ������ �޺κ��� ����ų ������
	char * bufferEnd = buffer + strlen(buffer) - 1;
	// ������ �޺κ��� ����Ű�� �����ʹ� �ݵ�� ���� �����ּҺ��� ũ�Ƿ�
	// ������ �ּҹ�ȣ�� ���� ���Ѵ�
	while (buffer <= bufferEnd)
	{
		// ������ �̵�, ������ ����
		*movepointer++ = *bufferEnd--;
	}
	// C ���ڿ��� ���ڿ��� ���� NULL�� ǥ���ϹǷ� NULL�߰�
	*movepointer = NULL;
	// ������ temp���۸� �������۷� ����
	strcpy(buffer, tempbuffer);
	// �޸� ����
	free(tempbuffer);
}

/*
Idea
���ڿ� -> ����
�����ڸ� ���ڿ����� ������ ���ؼ� ����
������ �ڸ����� ���� ����ġ�� ����
*/
int myatoi(char * buffer)
{
	// ������ ���ϰ�
	int ret = 0;
	// ����ġ
	int b = 1;

	// ���ڿ��� ���κ��� ������ �ֵ��� ������ ����
	char * temp = buffer + strlen(buffer) - 1;
	// ���ڿ��� ���� �ּҴ� ������ ���ڿ� �����ּҺ��� ũ�Ƿ� 
	// ������ �ּҹ�ȣ�� ���� ���Ѵ�
	while (buffer <= temp)
	{
		// ���ڿ��� �ش��ϴ� ���� �ƽ�Ű�ڵ� �������� �� �� �ڸ��� ����ġ�� ����
		ret += (*temp-- - '0') * b;
		// ����ġ�� �ڸ����� �ö󰥶� 10�辿 Ŀ��
		b *= 10;
	}
	return ret;
}

/*
Idea
���� -> ���ڿ� ��ȯ
���ڸ� �ڸ����� �ϳ��� �����Ѵ�
������ ���ڿ��� �ϳ��� ��ȯ�� ����(���� ����)
*/
void myitoa(char * buffer, int size, int num)
{
	int i = 0;

	for (i = 0;; i++)
	{
		// 10�� �������� ���ϸ� 1�� �ڸ����� ���� �� �ְ� ���⿡ �ƽ�Ű�ڵ尪�� �������ָ� ���ڿ��� ��
		buffer[i] = num % 10 + '0';
		// 1���ڸ� ���ڴ� �и������Ƿ� ������ 10���� ����
		num /= 10;
		// �����µ� 0�̸� ���̻� ���ڰ� ���°�
		if (num == 0)
			break;
	}
	// C ���ڿ��� ���ڿ��� ���� NULL�� ǥ���ϹǷ� NULL�߰�
	buffer[i + 1] = NULL;
	// ���ڿ��� ���� �������ֱ� ������ mystrrev�� ������
	mystrrev(buffer, size);
}

void main()
{
	//int a[5] = { 3,4,1,5,2 };
	//check(a,5);


	//char a[] = "abcdefghijklmnopqrstuvwxyz";
	//puts(a);
	//put_a(a);

	//char dst[100];
	//char src[] = "abcde";

	//mystrcpy(dst, src);
	//mystrcat(dst, "zzz");
	//puts(dst);


	//int a;
	//int *p;
	//int **k;

	//p = &a;
	//k = &p;

	//scanf("%d", &a);
	//printf("%d\n", a);

	//scanf("%d", p);
	//printf("%d\n", *p);

	//scanf("%d", *k);
	//printf("%d\n", **k);


	//int a = 7;
	//int *p;
	//intconnect(&a, &p);
	//printf("%d\n", *p);


	//int a = 10, b = 20;
	//int *ap = &a, *bp = &b;
	//int **app = &ap;
	//int **bpp = &bp;

	//swap1(&a, &b);
	//swap2(&ap, &bp);
	//swap3(&app, &bpp);
	//swap4(&ap, &bp);
	//swap5(&app, &bpp);
	//swap6(&app, &bpp);

	//int a = 100;
	//middle(&a);
	//printf("%d\n", a);

	//const char *p[3] = { "abc", "bbb", "ccc" };
	//printf("%s\n", p[0]);

	//char a[] = "abc";
	//char b[4] = "abc";
	//char c[10];
	//strcpy(c, "abc");
	//c[0] = 'z';

	//char * p = "abc";
	//char *k;
	//k[0] = 'z';
	//k = "abc";
	//strcpy(k, "abc");

	//char * a = "abc";
	//char *b[3] = { "abc", "abc", "abc" };
	//printf("%x %x %x\n", g, a, b[0]);

	
	//int a[2][3];
	//get_num(a);
	//put_num(a);


	//int a[3][4] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	//strrev() // ���ڿ� ������ �Լ�
	//atoi // ���ڷ� �ٲٴ��Լ�
	//itoa // ���ڷ� �ٲٴ��Լ�

	char buffer[128];
	int num;

	scanf("%s %d", buffer, &num);
	int ret = 0;

	for (int i = 0; i < num; i++)
	{
		ret = myatoi(buffer);
		mystrrev(buffer, 128);
		ret += myatoi(buffer);
		myitoa(buffer, 128, ret);
		printf("%d\n", ret);
	}

	system("pause");
	return;
}