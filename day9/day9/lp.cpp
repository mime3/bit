#include <stdio.h>
#include <stdlib.h>
#define __KERNEL__
#include "list.h"
#define list_entry(ptr, type, member) \
 ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
//list_entry�� �̿��Ͽ� ���� ����ü�� �����(a,b,c,d,x,y,z)�� �̿��� 
//����ü�� ù �ּҸ� ����ϴ� main�Լ��� �ϼ��Ͻÿ�

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

//-������ ���� ��µǰ� �Ͻÿ�
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
//����Ϸ��� �ƹ� Ű�� �����ʽÿ� . . .



//list.h(������ ���Ϸ� ���� ������ Ŀ�� ���)������ include �� �� �ֵ��� �����Ͻÿ�
//inline�̳� prefetch�� �������� �ʴ� ����̴�.

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
	//head�� �޸� �Ҵ��Ų�� 
	head = (Node *)malloc(Node_SIZE);

	//head ����ü ����� list������ ����� list�� ����Ű�� �ʱ�ȭ��Ű��
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


	list_add(ADRS(a), ADRS(head));		//list_add �Լ��� �̿��Ͽ� head�ڿ� a�� ����

	print_all();
	list_add(ADRS(b), ADRS(head));	//list_add �Լ��� �̿��Ͽ� head�ڿ� b�� ����
	print_all();
	list_del(head->list.next);		// list_del�Լ��� �̿��Ͽ� head�ڿ� �� ����
	print_all();
	free(a);
	free(b);
	free(head);

	getchar();
}

