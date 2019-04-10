#include <stdio.h>

//typedef void v;
//typedef v fv(int);
//typedef fv * pfv;
//typedef pfv fpfv();
//
////int(*(*)())();
//
//typedef int ic;
//typedef ic fic();
//typedef fic * pfic;
//typedef pfic fpfic();
//typedef fpfic * pfpfic;
//
//char *(*(*var)())[10];
//typedef char * pc;
//typedef pc apc[10];
//typedef apc * papc;
//typedef papc fpapc();
//typedef fpapc * pfpapc;
//
////void(*signal(int signum, void(*handler)(int)))(int);
//
//fpfv signal;  // void(*signal())(int)
//
//void func(int a)
//{
//	puts("func");
//}
//
//void(*signal())(int) // 포인터를 리턴, 그 포인터는 리턴이 void이고 인자가 int인 함수의 포인터
//{
//	return func;
//}
//
//int main()
//{
//	signal()(10);
//	getchar();
//}
//
////void(*signal(int signum, void(*handler)(int)))(int)
////{
////	return nullptr;
////}

#ifdef FPP
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  
#define loop(v, lo, hi) for((v)=(lo); (v)<(hi); (v)++)

int sum(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int multi(int a, int b) { return a * b; }
int divv(int a, int b) { return a / b; }
int mod(int a, int b) { return a % b; }

// calculator3과 typedef_calculator3이 동일한 동작을 하도록 FP, FPP를 typedef를 이용하여 작성하세요.
typedef int(*FP)(int, int);   // FP 작성
typedef FP FPP[5];   // FPP 작성

// calculator3은  함수 포인터 배열을 매개변수로 받고 함수 포인터를 반환하는 함수 
// typedef_calculator3과 동일한 선언이 되도록 calculator3의 헤더 부분을 작성합니다.
// typedef 사용금지
int(*calculator3(int(*fp[5])(int, int), int arr_size))(int, int)
{
	int low = 0;
	int high = arr_size - 1;
	int random_Num = rand() % (high - low) + low; //난수 발생범위를 low에서 high 범위내에 출력되는 코드
	return fp[random_Num];
}

FP typedef_calculator3(FPP fp, int arr_size)
{
	return calculator3(fp, arr_size);
}

// calculator2는 함수 포인터 배열을 매개변수 받는 함수
//    calculator2 함수는 arr_size 범위내로 난수발샘
//    사칙연산을 위한 피연산자는 11,7로 고정
//    난수에 따라 함수 수행 후 출력
//    수행된 함수 포인터를 반환함 

int calculator2(int(*fp[5])(int, int), char optor[5], int arr_size)
{
	int random_Num;
	int fir = 11, sec = 7;
	int low = 0;
	int high = arr_size - 1;

	printf("난수 발생 범위 %d ~ %d\n", low, high);

	random_Num = rand() % (high - low) + low; //난수 발생범위를 low에서 high 범위내에 출력되는 코드
	printf("난수 : %d\n", random_Num);
	printf("함수 실행 : %d %c %d = %d\n", fir, optor[random_Num], sec, fp[random_Num](fir, sec));
	return random_Num;
}

int typedef_calculator2(FPP fp, char* optor, int arr_size) {
	return calculator2(fp, optor, arr_size);
}

//calculator는 함수 포인터 배열을 인수로 받는 함수 
//fir와sec값으로 모든 사칙연산을 구현 출력하시오
int calculator(int(*fp[5])(int, int), int arr_size)
{
	int dx;
	int fir = 11, sec = 7;

	printf("%d + %d = %d\n", fir, sec, fir + sec);
	printf("%d - %d = %d\n", fir, sec, fir - sec);
	printf("%d * %d = %d\n", fir, sec, fir * sec);
	printf("%d / %d = %d\n", fir, sec, fir / sec);
	puts("");
	return fir;
}

int typedef_calculator(FPP fp, int arr_size) {
	return calculator(fp, arr_size);
}

int main(void) {
	int(*fpa[])(int, int) = { sum, sub, multi, divv, mod };  // 1. fpa는 함수 포인터 배열 
	char optor[] = { '+', '-', '*', '/', '%' };
	int dx;


	srand(time(NULL));

	// typedef 를 사용하지 않은 함수 호출 
	calculator(fpa, sizeof(fpa) / sizeof(fpa[0]));

	calculator2(fpa, optor, sizeof(fpa) / sizeof(fpa[0]));
	puts("");
	loop(dx, 0, 5)
	{
		Sleep(300);
		printf("random RUN!! : %d\n", calculator3(fpa, sizeof(fpa) / sizeof(fpa[0]))(10, 3));
	}

	// typedef 를 사용한 함수 호출     
	puts("");
	typedef_calculator(fpa, sizeof(fpa) / sizeof(fpa[0]));

	typedef_calculator2(fpa, optor, sizeof(fpa) / sizeof(fpa[0]));
	puts("");
	loop(dx, 0, 5)
	{
		Sleep(300);
		printf("random RUN!! : %d\n", typedef_calculator3(fpa, sizeof(fpa) / sizeof(fpa[0]))(10, 3));
	}
	getchar();
	return 0;
}

#else
#include "Queue.h"
#define QUEUE_SIZE 5
int queue[QUEUE_SIZE];
int front, rear;

void queue_Init()
{
	front = rear = 0;
}

bool queue_Put(int data)
{
	if ((rear + 1) % QUEUE_SIZE == front)
		return false;
	queue[rear] = data;
	rear = ++rear % QUEUE_SIZE;
	return true;
}

bool queue_Get(int * outData)
{
	if (front == rear)
		return false;
	*outData = queue[front];
	front = ++front % QUEUE_SIZE;
	return true;
}

void queue_Print()
{
	int move = front;
	while (move != rear)
	{
		printf("%d ", queue[move]);
		move = ++move % QUEUE_SIZE;
	}
}

int main()
{
	//bool ret;
	//queue_Init();
	//ret = queue_Put(5); // 5
	//ret = queue_Put(4); // 5 4
	//ret = queue_Put(3); // 5 4 3
	//ret = queue_Put(2); // 5 4 3 2
	//ret = queue_Put(1); // fail
	//int data;
	//ret = queue_Get(&data); // 4 3 2
	//ret = queue_Put(5); // 4 3 2 5
	//ret = queue_Get(&data); // 3 2 5
	//ret = queue_Get(&data); // 2 5

	//queue_Print();
	//puts("");


	//Queue<int> q;
	//ret = q.EnQueue(5); // 5
	//ret = q.EnQueue(4); // 5 4
	//ret = q.EnQueue(3); // 5 4 3
	//ret = q.EnQueue(2); // 5 4 3 2
	//ret = q.EnQueue(1); // 5 4 3 2
	//ret = q.DeQueue(&data); // 4 3 2 
	//ret = q.DeQueue(&data); // 3 2
	//ret = q.EnQueue(5);	// 3 2 5
	//q.Print();

	getchar();
	return 0;
}

#endif