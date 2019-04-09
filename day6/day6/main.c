#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define RESET
//#define STRUCT_SORT
//#define STRUCT_POINTER_ARRAY_SORT
//#define QUICK_SORT
/*
list_delete
list_add_sort
{ List * nw, *prv, *cmp ...}

��������, ��������, ������������

���ǹ��̳� �ݺ����� �����ϰ� �ϴ°��� ����ȭ (ü�� ����)
*/
#ifdef RESET
struct engine
{
	int piston;
	int fan;
	int pipe;
};

struct car
{
	struct engine *sedan;
	struct engine *sports;
};

void hyundai(struct car *man)
{
	struct engine * se = man->sedan;

	se->piston = 50;
	se->fan = 30;
	se->pipe = 20;
}

#define swap(a,b) do{int t = a; a = b; b = t;}while(0)
int partition(int arr[], int left, int right)
{
	int l = left;
	int r = right;
	int pivot = arr[l];

	while (l < r)
	{
		// pivot ���� ū�� ã��
		while (arr[l] <= arr[pivot])
		{
			l++;
		}

		// pivot���� ������ ã��
		while (arr[r] > arr[pivot])
		{
			r--;
		}

		if (l < r)
		{
			swap(arr[l], arr[r]);
		}
	}
	swap(arr[pivot], arr[r]);
	return r;
}

int myquick(int arr[], int left, int right)
{
	int pivot = partition(arr, left, right);
	if (left < pivot - 1)
		myquick(arr, left, pivot - 1);
	if (pivot + 1 < right)
		myquick(arr, pivot + 1, right);
}

unsigned int checksum(char * buffer)
{
	return (unsigned int)*buffer;
}

// ��������
void isort(char * a[], int n)
{
	int i;
	int j;
	char * t;
	for (i = 1; i < n; i++)
	{
		t = a[i];	// ���� ����
		j = i;		// �̵� �ε���
		unsigned int check1 = checksum(a[j - 1]);
		unsigned int check2 = checksum(t);
		// üũ�� ��
		//while (j > 0 && check1 < check2) // 0������ Ȯ��
		while (j > 0 && strcmp(a[j - 1], t) > 0)
		{
			// ������ �̵�
			a[j] = a[j - 1];
			j--;
		}
		a[j] = t;
	}
}

char * names[] = { "����", "���ؿ�", "�պ���", "�����", "���α�", "����", "�����",
	"�ڼ���", "�ڼ���", "�ŵ���", "�̰��", "������", "Ȳ����", "������",
	"��ȣ��", "���϶�", "�̽¿�", "������", "������", "������", "������" };

//int main()
//{
//	// 
//	//struct engine e;
//	//struct car hi;
//	//hi.sedan = &e;
//	//hyundai(&hi);
//	//printf("%d %d %d \n", hi.sedan->piston, hi.sedan->fan, hi.sedan->pipe);
//
//
//	//int arri[] = { 3,4,1,5,2,8,9,6,10,7 };
//	//myquick(arri, 0, 9);
//
//	unsigned int check = checksum(names[0]);
//	isort(names, 20);
//
//	for (int i = 0; i < 20; i++)
//		printf("%s ", names[i]);
//
//	getchar();
//	return 0;
//}

void printInt(int *arr, int size);
void printDbl(double *arr, int size);
void printstr(char *arr[], int size);


int comp_i(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

//���̺귯�� �����ϴ� qsort�� ���� comp_d �Լ� �ϼ�
int comp_d(const void* a, const void* b)
{
	if (*(double*)a < *(double*)b)
		return -1;
	else if (*(double*)a == *(double*)b)
		return 0;
	else
		return 1;
}

//���̺귯�� �����ϴ� qsort�� ���� comp_s �Լ� �ϼ�
int comp_s(const void * a, const void * b)
{
	return strcmp(*(char **)a, *(char **)b);
}


int main(void)
{
	isort(names, 20);

	for (int i = 0; i < 20; i++)
		printf("%s ", names[i]);
	printf("\n");


	int arri[] = { 3,4,1,5,2,8,9,6,10,7 };
	double arrd[] = { 3.2, 5.6, 4.3, 8.7, 2.3, 4.5, 2.1, 2.3, 4.6, 4.5 };
	char * arrs[] = { "����", "���ؿ�", "�պ���", "�����", "���α�",
		"����", "�����", "�ڼ���", "�ڼ���", "�ŵ���",
		"�̰��", "������", "Ȳ����", "������", "��ȣ��",
		"���϶�", "�̽¿�", "������", "������", "������",
		"������" };

	int(*a)(const void*, const void*) = comp_i;
	qsort(arri, sizeof(arri) / sizeof(arri[0]), sizeof(int), comp_i);
	printInt(arri, sizeof(arri) / sizeof(arri[0]));

	qsort(arrd, sizeof(arrd) / sizeof(arrd[0]), sizeof(double), comp_d);
	printDbl(arrd, sizeof(arrd) / sizeof(arrd[0]));

	//���̺귯�� qsort�� �̿��Ͽ� 2�����迭�� �ִ� ���ڿ��� �����սô�.

	//printf("%d", sizeof(arrs));

	printstr(arrs, sizeof(arrs) / sizeof(arrs[0]));
	qsort(arrs, sizeof(arrs) / sizeof(arrs[0]), sizeof(arrs[0]), comp_s);
	printstr(arrs, sizeof(arrs) / sizeof(arrs[0]));

	getchar();
	return 0;
}
void printInt(int *arr, int size) {
	int dx = 0;
	for (dx = 0; dx < size; ++dx) {
		printf("%d ", arr[dx]);
	}
	printf("\n");
}

void printDbl(double *arr, int size) {
	int dx = 0;
	for (dx = 0; dx < size; ++dx) {
		printf("%.1f  ", arr[dx]);
	}
	printf("\n");
}

void printstr(char * arr[], int size) {
	int dx = 0;
	for (dx = 0; dx < size; ++dx) {
		printf("%s ", arr[dx]);
	}
	printf("\n");
}

void abc(char(*a)[7])
{
	a[10];
}

#endif
#ifdef STRUCT_SORT
//���� ����ü�� ���̺귯�� qsort�� ����Ͽ� itemname�� ������������ �����Ͻÿ�
typedef struct _volume
{
	char itemname[20];
	int unitprice;
	int count;
	int amount;
}volume;
int prd_item(const void *a, const void *b)
{
	return strcmp(((volume *)a)->itemname, ((volume *)b)->itemname);
}
main()
{
	volume prd[5] = {
	 { "ccc", 10,90,900 },
	{ "aaa", 20,80,1600 },
	{ "ddd", 30,70,2100 },
	{ "eee", 40,60,2400 },
	{ "bbb", 50,50,2500 }
	};
	int dx;

	qsort(prd, 5, sizeof(prd[0]), prd_item);


	for (dx = 0; dx < 5; dx++)
		printf("%s %d %d %d\n", prd[dx].itemname,
			prd[dx].unitprice, prd[dx].count, prd[dx].amount);

	getchar();

}
#endif


//���� ����ü������ �迭�� ���̺귯�� qsort�� ����Ͽ� name�� ������������ �����Ͻÿ�
#ifdef STRUCT_POINTER_ARRAY_SORT

typedef struct _node node;
struct _node {
	char name[10];
	struct _node *next;
};
//int gg = 0;
int cmp_node(const void *a, const void *b)
{
	return strcmp((*(node**)a)->name, (*(node**)b)->name);
}
node *p, *q;
main()
{
	node *k[4];

	p = (node*)malloc(sizeof(node));
	strcpy(p->name, "ccc");
	p->next = NULL;
	q = (node*)malloc(sizeof(node));
	strcpy(q->name, "aaa");
	q->next = NULL;


	k[0] = q;
	k[1] = p;
	k[2] = (node*)malloc(sizeof(node));
	strcpy(k[2]->name, "bbb");
	qsort(k, 3, sizeof(node*), cmp_node);

	puts("\n-----");
	printf("%s\n", k[0]->name);
	printf("%s\n", k[1]->name);
	printf("%s\n", k[2]->name);

	getchar();
}
#endif // STRUCT_POINTER_ARRAY_SORT

#ifdef QUICK_SORT
typedef int(*FCMP)(const void *, const void *);
int cmp_i(const void *p, const void*k)
{
	return -(*(int *)p - *(int *)k);
}

int cmp_s(const void *p, const void*k)
{
	return strcmp((const char *)p, (const char *)k);
}

void *func(void *base, size_t num, size_t width, FCMP fcmp)
{
	//���������� cmp_i�� cmp_s�� ȣ���Ѵ� //����� -1(����), 0, 1(���)�� �����Ѵ�.
	printf("%d\n", fcmp(base, (char *)base + width));
	return 0;
}
void main()
{
	int ab[5] = { 10000000,3,1,5,2 };
	char bc[10][10] = { "aaaa","aaaa" };

	func(ab, 5, sizeof(int), cmp_i);
	func(bc, 2, sizeof(bc[0]), cmp_s);

	getchar();

	//char **a;
	//char ***pa = &a;

	//char *b[2];
	//char **pb = b;

	//char c[2][3];
	//char (*pc)[3] = c;

	//char *d[2][3] = { "aa","bb","cc","dd","ee","ff" };
	//char *(*pd)[3]= d;

	//char(*e)[2][3] = 0; // �迭������ ����
	//char (**pe)[2][3] = &e;

	//char(*f[2])[3];
	//char(**pf)[3] = f;


	char *x[2][3];
	char *(*px)[3] = x;
	char *(**ppx)[3] = &px;

	char **xx[2][3];
	char **(*pxx)[3] = xx;
	char **(**ppxx)[3] = &pxx;

	char aa[7][3];
	char bb[2][3];
	char (*pab[2])[3] = { aa,bb };



	getchar();
}


#endif