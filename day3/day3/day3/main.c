#include <stdio.h>
#include <windows.h>
#pragma warning(disable:4996)
// 배열 넘기기
void check(int * p, int size)
{
	// size를 넘겨야 구현가능
}

// k가 나올때까지 출력 -> puts
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
문자열 뒤집기
뒤집을 문자열을 저장할 공간을 동적할당 후
원본버퍼의 뒤부터 읽어서 한글자씩 복사한뒤
동적버퍼를 원본 버퍼에 복사함
*/ 
void mystrrev(char * buffer, int size)
{
	// 동적버퍼 동적 할당
	char * tempbuffer = (char *)malloc(size);
	// 한글자씩 복사로 인해 포인터가 이동하기떄문에 temp를 보존하고 움직일 포인터를 새로 만듬
	char * movepointer = tempbuffer;
	// 원본 버퍼의 뒷부분을 가리킬 포인터
	char * bufferEnd = buffer + strlen(buffer) - 1;
	// 버퍼의 뒷부분을 가리키는 포인터는 반드시 원본 시작주소보다 크므로
	// 포인터 주소번호를 직접 비교한다
	while (buffer <= bufferEnd)
	{
		// 포인터 이동, 데이터 복사
		*movepointer++ = *bufferEnd--;
	}
	// C 문자열은 문자열의 끝을 NULL로 표시하므로 NULL추가
	*movepointer = NULL;
	// 뒤집힌 temp버퍼를 원본버퍼로 복사
	strcpy(buffer, tempbuffer);
	// 메모리 해제
	free(tempbuffer);
}

/*
Idea
문자열 -> 숫자
일의자리 문자열부터 끝까지 더해서 만듬
루프시 자리수에 대한 가중치를 곱함
*/
int myatoi(char * buffer)
{
	// 저장할 리턴값
	int ret = 0;
	// 가중치
	int b = 1;

	// 문자열의 끝부분을 읽을수 있도록 포인터 세팅
	char * temp = buffer + strlen(buffer) - 1;
	// 문자열의 끝의 주소는 언제나 문자열 시작주소보다 크므로 
	// 포인터 주소번호를 직접 비교한다
	while (buffer <= temp)
	{
		// 문자열에 해당하는 수를 아스키코드 보정값을 뺀 후 자리수 가중치를 곱함
		ret += (*temp-- - '0') * b;
		// 가중치는 자리수가 올라갈때 10배씩 커짐
		b *= 10;
	}
	return ret;
}

/*
Idea
숫자 -> 문자열 변환
숫자를 자리마다 하나씩 분해한다
분해후 문자열로 하나씩 변환후 저장(순서 주의)
*/
void myitoa(char * buffer, int size, int num)
{
	int i = 0;

	for (i = 0;; i++)
	{
		// 10의 나머지를 구하면 1의 자리수를 얻을 수 있고 여기에 아스키코드값을 보정해주면 문자열이 됨
		buffer[i] = num % 10 + '0';
		// 1의자리 숫자는 분리했으므로 원본을 10으로 나눔
		num /= 10;
		// 나눴는데 0이면 더이상 숫자가 없는것
		if (num == 0)
			break;
	}
	// C 문자열은 문자열의 끝을 NULL로 표시하므로 NULL추가
	buffer[i + 1] = NULL;
	// 문자열이 현재 뒤집혀있기 때문에 mystrrev로 뒤집음
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

	//strrev() // 문자열 뒤집는 함수
	//atoi // 숫자로 바꾸는함수
	//itoa // 문자로 바꾸는함수

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