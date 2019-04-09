
#include <random>
#include <stdio.h>
#include <stdarg.h>
//#define TEST

#ifdef TEST
using namespace std;

random_device seed;
mt19937 generator(seed());

int main()
{
	//generator.min();
	//uniform_int_distribution<> undis(0, 20);
	//undis(generator);

	int a[2][2][2];
	printf("%d \n", sizeof(&a[0][0][0]));
	getchar();
	return 0;
}

#else
typedef int ElementType;

typedef struct tagNode
{
	ElementType Data;
	struct tagNode* PrevNode;
	struct tagNode* NextNode;
} Node;

Node* CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = NewData;
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

/*  ��� �߰� */
void AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL)
	{
		*Head = NewNode;
		(*Head)->NextNode = *Head;
		(*Head)->PrevNode = *Head;
	}
	else
	{
		Node* Tail = (*Head)->PrevNode;

		Tail->NextNode->PrevNode = NewNode;
		Tail->NextNode = NewNode;

		NewNode->NextNode = *Head;
		NewNode->PrevNode = Tail;
	}
}

void Print(Node * head)
{
	Node * move = head;
	Node * tail = head->PrevNode;
	do
	{
		printf("%d ", move->Data);
		move = move->NextNode;
	} while (move != head);
}

#define STACK_SIZE 5
int STACK[STACK_SIZE];
int top;

void stack_Init()
{
	top = -1;
}

bool stack_Push(int data)
{
	if (STACK_SIZE - 1 <= top)
		return false;
	STACK[++top] = data;
	return true;
}

bool stack_Pop(int * data)
{
	if (top < 0)
		return false;
	*data = STACK[top--];
	return true;
}


//typedef char *  va_list;
//#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )
//#define va_start(ap,v)  ( ap = (va_list)&v + _INTSIZEOF(v) )
//#define va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
//#define va_end(ap)      ( ap = (va_list)0 )

float average(int num, ...)
{
	va_list arg_ptr;
	int cnt, total = 0;

	va_start(arg_ptr, num);
	for (cnt = 0; cnt < num; cnt++)
	{
		total += va_arg(arg_ptr, int);
	}
	va_end(arg_ptr);
	return ((float)total / num);
}


#include "URLStack.h"
URLStack url;
int jumpSize = 0;

void PrintMenu()
{
	printf("\n");
	const char * page = nullptr;
	url.Peek(&page);
	//if (!url.Peek(&page))
	//	page = "about:blank";
	printf("���� �������� �� ������ : %s\n", page != nullptr ? page : "about:blank");
	printf("==============================\n");
	printf("1. URL ����\n");
	printf("2. �湮 ��� ����\n");
	printf("3. �ڷ�\n");
	printf("4. ������\n");
	printf("0. ����\n");
	printf("==============================\n");
}

void ConnectURL()
{
	printf("\n");
	char * buffer = new char[32];
	printf("URL : ");
	scanf_s("%s", buffer, 32);
	url.Push(buffer);

	// top -> cur ����
	while (url._top < url._current)
	{
		url.Pop(&buffer);
		delete buffer;
	}
}

void PrintHistory()
{
	int count = 1;
	printf("\n");
	printf("�ڷ� �̵� �� �� �ִ� ���\n");
	printf("============================\n");
	for (int i = 0; i < url._top; i++)
	{
		if (i == url._current)
		{
			printf("\n");
			printf("������ �̵� �� �� �ִ� ���\n");
			printf("============================\n");
			count = 1;
		}
		printf("%d. %s\n", count++, url._history[i]);
	}
	printf("\n");
}

void Back()
{
	if (url._current < 0)
		printf("�Ұ���\n");
	else
		url._current--;
}

void Go()
{
	if (url._current >= MAX_HISTORY || url._current == url._top)
		printf("�Ұ���\n");
	else	
		url._current++;
}

int main(void)
{
	//int   i = 0;
	//int   Count = 0;
	//Node* List = NULL;
	//Node* NewNode = NULL;
	//Node* Current = NULL;

	///*  ��� 5�� �߰� */
	//for (i = 0; i < 5; i++) //�� �ݺ����� 3�� ���� �������� �޸� ��� �׸���
	//{
	//	NewNode = CreateNode(i);
	//	AppendNode(&List, NewNode);
	//	Print(List);
	//	printf("\n");
	//}

	//STACK
	//stack_Init();
	//stack_Push(5);
	//stack_Push(4);
	//stack_Push(3);
	//stack_Push(2);
	//stack_Push(1);
	//stack_Push(7);
	//int pop;
	//stack_Pop(&pop);
	//printf("%d\n", pop);
	//stack_Pop(&pop);
	//printf("%d\n", pop);
	//if (!stack_Pop(&pop))
	//	printf("stack empty\n");
	//else
	//	printf("%d\n", pop);

	//float x;
	//x = (average(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
	//printf("first avg is %f\n", x);
	int input = 1;

	while (input)
	{
		PrintMenu();
		printf("�޴� �Է� : ");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			ConnectURL();
			break;
		case 2:
			PrintHistory();
			break;
		case 3:
			Back();
			break;
		case 4:
			Go();
			break;
		default:
			break;
		}
	}

	getchar();
	return 0;
}

#endif