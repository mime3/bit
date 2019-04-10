#include <stdio.h>
#include <queue>
#include "Queue.h"


int arr[12] = { 72, 81, 64, 31, 29 , 43, 77, 26, 15, 48, 25, 95 };
int ret[12];

Queue<int> one[10];
Queue<int> two[10];

void bukitsort(int arr[], int ret[], int size)
{
	for (int i = 0; i < size; i++)
	{
		one[arr[i] % 10].EnQueue(arr[i]);
	}

	int out;
	for (int i = 0; i < 10; i++)
	{
		while (one[i].DeQueue(&out))
		{
			two[out / 10].EnQueue(out);
		}
	}

	int index = 0;
	for (int i = 0; i < 10; i++)
	{
		while (two[i].DeQueue(&out))
		{
			ret[index++] = out;
		}
	}

}

int main()
{
	bukitsort(arr, ret, 12);
	for (auto& num : ret)
	{
		printf("%d ", num);
	}
	puts("");
	getchar();
	return 0;
}