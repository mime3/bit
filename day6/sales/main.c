#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)
typedef struct node NODE;
typedef struct item ITEM;
struct node
{
	ITEM * item;
	NODE * next;
};

struct item
{
	char name[32];
	int value;
	int volume;
	int sales;
};

NODE * head;
NODE * tail;

void list_Init() 
{
	head = (NODE *)malloc(sizeof(NODE));
	tail = (NODE *)malloc(sizeof(NODE));
	head->next = tail;
	tail->next = tail;
}

void list_Add_Front(ITEM * item)
{
	NODE * newNode = (NODE *)malloc(sizeof(NODE));
	newNode->item = item;
	newNode->next = head->next;
	head->next = newNode;
}

NODE * list_Erase_Find(char * name)
{
	NODE * move = head->next;
	while (move->next != tail)
	{
		if (!strcmp(move->next->item->name, name))
			return move;
		move = move->next;
	}
	return NULL;
}

int list_Erase(char * name)
{
	NODE * preTarget = list_Erase_Find(name);
	if (preTarget == NULL)
		return 0;

	NODE * target = preTarget->next;
	preTarget->next = target->next;
	free(target->item);
	free(target);
	return 1;
}

ITEM * list_Find(char * name)
{
	NODE * move = head->next;
	while (move != tail)
	{
		if(!strcmp(move->item->name, name))
			return move->item;
		move = move->next;
	}
	return NULL;
}

ITEM * newItem(char name[32], int value)
{
	ITEM * item = (ITEM *)malloc(sizeof(ITEM));
	strcpy(item->name, name);
	item->value = value;
	return item;
}

void LoadList()
{
	FILE * itemList = fopen("item.txt", "r");

	char buffer[32] = { 0, };
	char * name;
	int value;
	while (fgets(buffer, 32, itemList))
	{
		name = strtok(buffer, " ");
		value = atoi(strtok(NULL, " "));
		ITEM * item = newItem(name, value);
		list_Add_Front(item);
	}
	fclose(itemList);
}

void LoadData()
{
	FILE * itemData = fopen("sales.txt", "r");

	char buffer[32];
	char * name;
	int volume;

	while (fgets(buffer, 32, itemData))
	{
		name = strtok(buffer, " ");
		volume = atoi(strtok(NULL, " "));
		ITEM * item = list_Find(name);
		if (item != NULL)
		{
			item->volume = volume;
			item->sales = volume * item->value;
		}
	}
	fclose(itemData);
}

void PrintMenu()
{
	printf("===== M E N U  =====\n");
	printf("1. 매출현황 출력\n");
	printf("2. 매출현황 내보내기\n");
	printf("3. 상품 찾기\n");
	printf("4. 상품 삭제\n");
	printf("5. 매출현황 배열\n");
	printf("6. 정렬\n");
	printf("7. 종료\n");
	printf("=====================\n");
	printf("메뉴를 선택하시오 : ");
}

void ItemPrint()
{
	printf("리스트 출력\n");
	NODE * node = head->next;
	int sum = 0;
	printf("==============================================\n");
	printf("%14s %6s %6s %10s\n", "이름", "가격", "판매량", "매출액");
	printf("----------------------------------------------\n");
	while (node != tail)
	{
		ITEM * item = node->item;
		printf("%14s %6d %6d %10d\n", item->name, item->value, item->volume, item->sales);
		sum += item->sales;
		node = node->next;
	}
	printf("==============================================\n");
	printf("%14s : %d\n","매출 합계", sum);
	printf("==============================================\n");
}

void ItemSave()
{
	FILE * list = fopen("itemlist.txt", "w");
	FILE * volume = fopen("volumelist.txt", "w");

	NODE * move = head->next;
	while (move != tail)
	{
		ITEM * item = move->item;
		fprintf(list, "%s %d\n", item->name, item->value);
		fprintf(volume, "%s %d\n", item->name, item->volume);
		move = move->next;
	}

	fclose(list);
	fclose(volume);
}

void ItemFind()
{
	char name[32];
	printf("상품이름 : ");
	scanf("%s", name);

	NODE * move = head->next;
	while (move->next != tail)
	{
		ITEM * item = move->item;
		if (strcmp(item->name, name) == 0)
		{
			printf("=======================================================\n");
			printf("%14s %6d %6d %10d\n", item->name, item->value, item->volume, item->value * item->volume);
			printf("=======================================================\n"); 
			return;
		}
		move = move->next;
	}
	printf("상품이 없음\n");
}

void ItemDelete()
{
	char name[32];
	printf("상품이름 : ");
	scanf("%s", name);

	if (list_Erase(name))
		printf("%s 삭제완료\n", name);
	else
		printf("상품이 없음\n");
}

ITEM itemArray[32];
int arraySize = 0;
void ArrayInit()
{
	int index = 0;
	NODE * move = head->next;
	while (move != tail)
	{
		ITEM * item = move->item;
		strcpy(itemArray[index].name, move->item->name);
		itemArray[index].value = move->item->value;
		itemArray[index].volume = move->item->volume;
		itemArray[index].sales = move->item->sales;
		move = move->next;
		index++;
	}
	arraySize = index;
}

int cmp_name_asc(const void *first, const void * second)
{
	return strcmp(((ITEM *)first)->name, ((ITEM *)second)->name);
}

int cmp_name_dsc(const void *first, const void * second)
{
	return -cmp_name_asc(first, second);
}

int cmp_value_asc(const void *first, const void * second)
{
	return ((ITEM *)first)->value - ((ITEM *)second)->value;
}

int cmp_value_dsc(const void *first, const void * second)
{
	return -cmp_value_asc(first, second);
}

int cmp_volume_asc(const void *first, const void * second)
{
	return ((ITEM *)first)->volume - ((ITEM *)second)->volume;
}

int cmp_volume_dsc(const void *first, const void * second)
{
	return -cmp_volume_asc(first, second);
}

int cmp_sales_asc(const void *first, const void * second)
{
	return ((ITEM *)first)->sales - ((ITEM *)second)->sales;
}

int cmp_sales_dsc(const void *first, const void * second)
{
	return -cmp_sales_asc(first, second);
}

void PrintArray()
{
	printf("배열 출력\n");
	int sum = 0;
	printf("================================================\n");
	printf("%14s %6s %6s %10s\n", "이름", "가격", "판매량", "매출액");
	printf("------------------------------------------------\n");
	for (int i = 0; i < arraySize; i++)
	{
		printf("%14s %6d %6d %10d\n", itemArray[i].name, itemArray[i].value, itemArray[i].volume, itemArray[i].sales);
		sum += itemArray[i].sales;
	}
	printf("===============================================\n");
	printf("%14s : %d\n", "매출 합계", sum);
	printf("===============================================\n");
}

void ItemSort()
{
	NODE * move = head->next;
	for (int i = 0; i < arraySize; i++)
	{
		strcpy(itemArray[i].name, move->item->name);
		itemArray[i].value = move->item->value;
		itemArray[i].volume = move->item->volume;
		move = move->next;
	}

	int criteria;
	int asc;
	printf("정렬 기준\n1. 이름,  2. 가격,  3. 판매량  4. 매출액\n  :");
	scanf("%d", &criteria);
	printf("정렬 방법\n1. 오름차순,  2. 내림차순\n  :");
	scanf("%d", &asc);

	if (asc == 1)
	{
		switch (criteria)
		{
		case 1:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_name_asc);
			break;
		case 2:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_value_asc);
			break;
		case 3:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_volume_asc);
			break;
		case 4:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_sales_asc);
			break;
		default:
			break;
		}
		PrintArray();
	}
	else if (asc == 2)
	{
		switch (criteria)
		{
		case 1:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_name_dsc);
			break;
		case 2:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_value_dsc);
			break;
		case 3:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_volume_dsc);
			break;
		case 4:
			qsort(itemArray, arraySize, sizeof(ITEM), cmp_sales_dsc);
			break;
		default:
			break;
		}
		PrintArray();
	}
	else
	{
		printf("입력 오류\n");
	}
}

int main()
{
	list_Init();
	LoadList();
	LoadData();
	int input;
	while (1)
	{
		//system("cls");
		PrintMenu();
		scanf("%d", &input);
		switch (input)
		{
		case 1: 
			ItemPrint();
			break;
		case 2: 
			ItemSave();
			break;
		case 3: 
			ItemFind();
			break;
		case 4:
			ItemDelete();
			break;
		case 5: 
			ArrayInit();
			PrintArray();
			break;
		case 6: 
			ArrayInit();
			ItemSort();
			break;
		case 7: 
			goto END;
			break;
		default:
			break;
		}
	}
END:
	getchar();
	return 0;
}