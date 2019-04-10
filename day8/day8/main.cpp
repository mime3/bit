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
//void(*signal())(int) // �����͸� ����, �� �����ʹ� ������ void�̰� ���ڰ� int�� �Լ��� ������
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

// calculator3�� typedef_calculator3�� ������ ������ �ϵ��� FP, FPP�� typedef�� �̿��Ͽ� �ۼ��ϼ���.
typedef int(*FP)(int, int);   // FP �ۼ�
typedef FP FPP[5];   // FPP �ۼ�

// calculator3��  �Լ� ������ �迭�� �Ű������� �ް� �Լ� �����͸� ��ȯ�ϴ� �Լ� 
// typedef_calculator3�� ������ ������ �ǵ��� calculator3�� ��� �κ��� �ۼ��մϴ�.
// typedef ������
int(*calculator3(int(*fp[5])(int, int), int arr_size))(int, int)
{
	int low = 0;
	int high = arr_size - 1;
	int random_Num = rand() % (high - low) + low; //���� �߻������� low���� high �������� ��µǴ� �ڵ�
	return fp[random_Num];
}

FP typedef_calculator3(FPP fp, int arr_size)
{
	return calculator3(fp, arr_size);
}

// calculator2�� �Լ� ������ �迭�� �Ű����� �޴� �Լ�
//    calculator2 �Լ��� arr_size �������� �����߻�
//    ��Ģ������ ���� �ǿ����ڴ� 11,7�� ����
//    ������ ���� �Լ� ���� �� ���
//    ����� �Լ� �����͸� ��ȯ�� 

int calculator2(int(*fp[5])(int, int), char optor[5], int arr_size)
{
	int random_Num;
	int fir = 11, sec = 7;
	int low = 0;
	int high = arr_size - 1;

	printf("���� �߻� ���� %d ~ %d\n", low, high);

	random_Num = rand() % (high - low) + low; //���� �߻������� low���� high �������� ��µǴ� �ڵ�
	printf("���� : %d\n", random_Num);
	printf("�Լ� ���� : %d %c %d = %d\n", fir, optor[random_Num], sec, fp[random_Num](fir, sec));
	return random_Num;
}

int typedef_calculator2(FPP fp, char* optor, int arr_size) {
	return calculator2(fp, optor, arr_size);
}

//calculator�� �Լ� ������ �迭�� �μ��� �޴� �Լ� 
//fir��sec������ ��� ��Ģ������ ���� ����Ͻÿ�
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
	int(*fpa[])(int, int) = { sum, sub, multi, divv, mod };  // 1. fpa�� �Լ� ������ �迭 
	char optor[] = { '+', '-', '*', '/', '%' };
	int dx;


	srand(time(NULL));

	// typedef �� ������� ���� �Լ� ȣ�� 
	calculator(fpa, sizeof(fpa) / sizeof(fpa[0]));

	calculator2(fpa, optor, sizeof(fpa) / sizeof(fpa[0]));
	puts("");
	loop(dx, 0, 5)
	{
		Sleep(300);
		printf("random RUN!! : %d\n", calculator3(fpa, sizeof(fpa) / sizeof(fpa[0]))(10, 3));
	}

	// typedef �� ����� �Լ� ȣ��     
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