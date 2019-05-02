#include <stdio.h>
#include <stdlib.h>
#define __KERNEL__
#include "list.h"
#define list_entry(ptr, type, member) \
 ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
//list_entry를 이용하여 다음 구조체의 각멤버(a,b,c,d,x,y,z)를 이용해 
//구조체의 첫 주소를 출력하는 main함수를 완성하시오

struct engine 
{
	char a[5];
	double b;
	int c[3];
};

struct car 
{
	char x[10];
	int y;
	struct engine z;
};


//void main()
//{
//	car bm;
//	printf("&bm : [ %x ]\n", &bm);
//	
//	printf("&bm car : [ %x ]\n", &bm.z);
//	printf("&bm car : [ %x ]\n", list_entry(&bm.z.b, car, z.b));
//
//	getchar();
//}

//-다음과 같이 출력되게 하시오
//
//************
//[Empty]
//* ***********
//[123]
//* ***********
//[789]
//[123]
//* ***********
//[123]
//계속하려면 아무 키나 누르십시오 . . .



//list.h(기존에 메일로 보낸 리눅스 커널 헤더)파일을 include 할 수 있도록 구현하시오
//inline이나 prefetch는 제공되지 않는 기능이다.

/* in include/linux/types.h */
//struct list_head {
//	struct list_head *next, *prev;
//};

typedef struct kernel_struct
{
	int key;
	struct list_head list;
}Node;
#define ADRS(lt) &(lt)->list

#define Node_SIZE (sizeof(Node))

Node *head;


void init_Node(void)
{
	//head를 메모리 할당시킨다 
	head = (Node *)malloc(Node_SIZE);

	//head 구조체 멤버인 list내부의 멤버가 list를 가리키게 초기화시키자
	INIT_LIST_HEAD(&head->list);
}

void print_all(void)
{
	struct list_head *temp;
	printf("************\n");
	list_for_each(temp, &head->list) 
	{
		Node *ps = list_entry(temp, Node, list);
		printf("[%d]\n", ps->key);
	}
}

int main()
{
	Node *a, *b;
	if ((a = (Node *)malloc(Node_SIZE)) == NULL)
		printf("[ Error ]\n");
	if ((b = (Node *)malloc(Node_SIZE)) == NULL)
		printf("[ Error ]\n");

	init_Node();
	a->key = 123; b->key = 789;


	print_all();

	if (list_empty(&head->list))
		printf("[ Empty ]\n");


	list_add(ADRS(a), ADRS(head));		//list_add 함수를 이용하여 head뒤에 a를 삽입

	print_all();
	list_add(ADRS(b), ADRS(head));	//list_add 함수를 이용하여 head뒤에 b를 삽입
	print_all();
	list_del(head->list.next);		// list_del함수를 이용하여 head뒤에 를 삭제
	print_all();
	free(a);
	free(b);
	free(head);

	getchar();
}

