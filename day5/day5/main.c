#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)


typedef struct num
{
	int fir;
	int sec;
}NUM;

void func1(int a, int b) { printf("%d\n", a + b); }
void func2(NUM * a) { printf("%d\n", a->fir + a->sec); }
void func3(NUM a[]) { printf("%d\n", a[0].fir + a[0].sec + a[1].fir + a[1].sec); }

typedef struct node NODE;
struct node
{
	int key;
	NODE * next;
};

NODE * head, *tail;

void list_init()
{
	head = (NODE *)malloc(sizeof(NODE)); // head노드
	tail = (NODE *)malloc(sizeof(NODE)); // tail노드

	head->next = tail;
	tail->next = tail;
}

void list_add_front(int data)
{
	NODE * newNode = (NODE *)malloc(sizeof(NODE));
	newNode->key = data;
	newNode->next = head->next;
	head->next = newNode;
}

void list_add_back(int data)
{
	NODE * newNode = (NODE *)malloc(sizeof(NODE));
	newNode->key = data;
	newNode->next = tail;
	NODE * preTail = head;
	while (preTail->next == tail)
	{
		preTail = preTail->next;
	}
	preTail->next = newNode;
}

void list_erase_back(int * data)
{
	// 단방향 링크리스트는 tail의 전전 노드를 찾아야함
	NODE * erasePreNode = head;
	while (1)
	{
		if (erasePreNode->next->next == tail)
			break;
		erasePreNode = erasePreNode->next;
	}
	*data = erasePreNode->next->key;
	free(erasePreNode->next);
	erasePreNode->next = tail;
}

void list_erase_front(int * data)
{
	NODE * temp = head->next->next;
	free(head->next);
	head->next = temp;
}

void list_print()
{
	NODE * node = head->next;
	while (node != tail)
	{
		printf("%d ", node->key);
		node = node->next;
	}
	printf("\n");
}

bool list_find(int data)
{
	NODE * node = head->next;
	while (node != tail)
	{
		if (node->key == data)
			return true;
		node = node->next;
	}
	return false;
}

bool list_erase(int data)
{
	NODE * preNode = head;
	while (preNode->next != tail)
	{
		if (preNode->next->key == data)
			break;
		preNode = preNode->next;
	}

	if (preNode->next == tail)
		return false;

	NODE * delNode = preNode->next;
	preNode->next = delNode->next;
	free(delNode);
	return true;
}

bool list_find_move_to_front(int data)
{
	NODE * preNode = head;
	while (preNode->next != tail)
	{
		if (preNode->next->key == data)
			break;
		preNode = preNode->next;
	}

	if (preNode->next == tail)
		return false;

	NODE * moveNode = preNode->next;
	preNode->next = moveNode->next;

	NODE * temp = head->next;
	head->next = moveNode;
	moveNode->next = temp;
	return true;

	// delete ver
	if (!list_erase(data))
		return false;

	list_add_front(data);
	return true;
}

void list_swap(NODE * preNode1, NODE * preNode2)
{
	NODE * target1 = preNode1->next;
	NODE * target2 = preNode2->next;
	NODE * target2_next = target2->next;

	preNode1->next = target2;
	if (target1->next != target2)
	{
		target2->next = target1->next;
		preNode2->next = target1;
		target1->next = target2_next;
	}
	else
	{
		target2->next = target1;
		target1->next = target2_next;
	}
}

bool swap_pre(int data)
{
	NODE * prepreNode = head;
	while (prepreNode->next->next != tail)
	{
		if (prepreNode->next->next->key == data)
			break;
		prepreNode = prepreNode->next;
	}

	if (prepreNode->next->next == tail)
		return false;

	NODE * preNode = prepreNode->next;
	NODE * target = preNode->next;

	prepreNode->next = target;
	preNode->next = target->next;
	target->next = preNode;
	return true;
}

void list_sort()
{
	NODE * preStartNode = head;
	NODE * startNode = head->next;
	NODE * moveNode = head->next;
	NODE * preMoveNode = head;
	NODE * minNode = moveNode;
	NODE * preMinNode = head;
	// 싱글링크이기때문에 pre노드 포인터 3개가 더 사용됨
	while (startNode->next != tail)
	{
		while (moveNode != tail)
		{
			if (moveNode->key < minNode->key)
			{
				preMinNode = preMoveNode;
				minNode = moveNode;
			}
			preMoveNode = moveNode;
			moveNode = moveNode->next;
		}
		if (minNode != startNode)
		{
			list_swap(preStartNode, preMinNode);
			preStartNode = minNode;
		}
		else
		{
			preStartNode = startNode;
			startNode = startNode->next;
		}

		// value swap ver
		//if (minNode != moveNode)
		//{
		//	int temp = minNode->key;
		//	minNode->key = startNode->key;
		//	startNode->key = temp;
		//}
		//startNode = startNode->next;

		moveNode = startNode;
		minNode = moveNode;
	}
}

struct subject
{
	int subname[5];
};

struct sung
{
	char name[10];
	float avg;
	struct subject sub;
};

void Input(struct sung * s)
{
	char * name[3] = { "국어", "영어", "수학" };
	for (int i = 0; i < 3; i++)
	{
		printf("사람이름 : ");
		scanf("%s", s[i].name);
		s[i].sub.subname[3] = 0;
		s[i].avg = 0;
		for (int j = 0; j < 3; j++)
		{
			printf("%s점수 : ", name[j]);
			scanf("%d", &s[i].sub.subname[j]);
			s[i].sub.subname[3] += s[i].sub.subname[j];
		}
		s[i].avg = (float)s[i].sub.subname[3] / 3;
	}
}

void CalRanking(struct sung s[]) 
{
	for (int i = 0; i < 3; i++)
	{
		int rank = 1;
		for (int j = 0; j < 3; j++)
		{
			if (s[i].sub.subname[3] < s[j].sub.subname[3])
				rank++;
		}
		s[i].sub.subname[4] = rank;
	}
}

void PrintList(struct sung s[])
{
	printf("성명 국어 영어 수학 총점 순위 평균\n");
	for (int i = 0; i < 3; i++)
	{
		printf("%3s  %3d  %3d  %3d  %3d    %d  %.1f\n", 
			s[i].name, 
			s[i].sub.subname[0],
			s[i].sub.subname[1], 
			s[i].sub.subname[2], 
			s[i].sub.subname[3], 
			s[i].sub.subname[4],
			s[i].avg);
	}

}

#define SLEEPTIME 500

int main()
{
	//NUM a = { 1,2 }, b = { 3,4 }, c[2] = { 5,6,7,8 };
	//func1(a.fir, a.sec);
	//func2(&b);
	//func3(&c);
	
	//struct sung s[3];
	//Input(s);
	//CalRanking(s);
	//PrintList(s);
	int data;
	int target = 3;
	list_init();

	int add = 0;
	while (1)
	{
		_sleep(SLEEPTIME);
		system("cls");
		int num = rand() % 10 + 1;
		if (list_find(num))
		{
			list_print();
			printf("중복\n");
			continue;
		}

		list_add_front(num);
		list_sort();
		add++;
		if (add == 10)
			break;

		list_print();
	}
	list_print();

	bool check = false;
	while (1)
	{
		int move;
		if (check)
		{
			printf("맨앞으로 옮길 정보 입력 : ");
			scanf("%d", &move);
			list_find_move_to_front(move);
		}
		else
		{
			printf("한칸 앞으로 옮길 정보 입력 : ");
			scanf("%d", &move);
			swap_pre(move);
		}
		list_print();
		check = !check;
	}

	system("pause");
	return 0;
}