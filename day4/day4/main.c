#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <io.h>
#include <stdbool.h>
#pragma warning(disable:4996)


void array_1to2(char * p)
{
	puts(p);
}

void array_2to2(char p[1000][10])
{
	puts(p[2]);
}

void print_a(char *p[])
{
	// 0��° abc���� bc��

	char * move = p[0];
	while (*move)
	{
		if (*move != 'a')
			putc(*move, stdout);
		move++;
	}
	// 1��° home���� h��
	move = p[1];
	while (*move)
	{
		if (*move == 'h')
			putc(*move, stdout);
		move++;
	}
	// 2��° print���� i��
	move = p[2];
	while (*move)
	{
		if (*move == 'i')
			putc(*move, stdout);
		move++;
	}
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int dvv(int a, int b) { return a / b; }

typedef int(*myfp_t)(int, int);
int temp(myfp_t p_func, int a, int b) { return p_func(a, b); }

void MakeBingo(int bingo[2][5][5])
{
	// �� �����
	for (int i = 0; i < 2; i++)
	{
		int num = 1;
		while (1)
		{
			int randX = rand() % 5;
			int randY = rand() % 5;

			if (bingo[i][randY][randX] != 0)
				continue;

			bingo[i][randY][randX] = num;


			if (num >= 25)
				break;
			num++;
		}
	}
}
void PrintBingo(int bingo[2][5][5])
{
	system("cls");
	// ���� ���
	printf("     user		   com\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (bingo[0][i][j] != 0)
				printf("%2d ", bingo[0][i][j]);
			else
				printf("%2s ", "X");
		}
		printf("      ");
		for (int j = 0; j < 5; j++)
		{
			if (bingo[1][i][j] != 0)
				printf("%2d ", bingo[1][i][j]);
			else
				printf("%2s ", "X");
		}
		printf("\n");

		//printf("%2d %2d %2d %2d %2d        %2d %2d %2d %2d %2d\n",
		//	bingo[0][i][0], bingo[0][i][1], bingo[0][i][2], bingo[0][i][3], bingo[0][i][4], 
		//	bingo[1][i][0], bingo[1][i][1], bingo[1][i][2], bingo[1][i][3], bingo[1][i][4]);
	}
}
void BingoSelect(int bingo[5][5], int input, int * x, int * y)
{
	bool find = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (bingo[i][j] == input)
			{
				bingo[i][j] = 0;
				*y = i;
				*x = j;
				find = true;
				break;
			}
		}
		if (find)
			break;
	}
}
void BingoSelect_Com(int bingo[5][5], int * x, int * y)
{
	int randX = 0;
	int randY = 0;
	while (1)
	{
		randX = rand() % 5;
		randY = rand() % 5;

		if (bingo[randY][randX] != 0)
		{
			bingo[randY][randX] = 0;
			*x = randX;
			*y = randY;
			break;
		}
	}
}
bool WinCheck(int bingo[5][5], int x, int y)
{
	int winPoint = 0;
	if (x == y)
	{
		for (int i = 0; i < 5; i++)
		{
			if (bingo[i][i] == 0)
				winPoint++;
			else
				break;
		}
		if (winPoint == 5)
			return true;
	}
	else if (x + y == 4)
	{
		for (int i = 0; i < 5; i++)
		{
			if (bingo[i][4 - i] == 0)
				winPoint++;
			else
				break;
		}
		if (winPoint == 5)
			return true;
	}
	winPoint = 0;

	// ���μ���
	for (int i = 0; i < 5; i++)
	{
		if (bingo[i][x] == 0)
			winPoint++;
		else
			break;
	}
	if (winPoint == 5)
		return true;
	winPoint = 0;

	for (int i = 0; i < 5; i++)
	{
		if (bingo[y][i] == 0)
			winPoint++;
		else
			break;
	}
	if (winPoint == 5)
		return true;
	return false;
}

int main(int argc, char *argv[])
{
	//char a[3][10] = { "abc", "defg", "zzzzzz" };
	//array_1to2(a[2]);
	//array_2to2(a);

	//char *a[3] = { "abc", "home", "print" };
	//print_a(a);


	//int temp[2] = { 0, };
	//char operator = 0;

	//for (int dx = 1; dx < argc; dx++)
	//{
	//	if (dx % 2 != 0)
	//		temp[dx / 2] = atoi(argv[dx]);
	//	else
	//		operator = argv[dx][0];
	//}

	//switch (operator)
	//{
	//case '+':
	//	printf("%d %c %d = %d\n",temp[0], operator, temp[1], temp[0] + temp[1]);
	//	break;
	//case '-':
	//	printf("%d %c %d = %d\n",temp[0], operator, temp[1], temp[0] - temp[1]);
	//	break;
	//case '*':
	//	printf("%d %c %d = %d\n",temp[0], operator, temp[1], temp[0] * temp[1]);
	//	break;
	//case '/':
	//	printf("%d %c %d = %d\n",temp[0], operator, temp[1], temp[0] / temp[1]);
	//	break;
	//default:
	//	printf("error\n");
	//	break;
	//}

	//int(*p[4])(int, int) = { add, sub, mul, dvv }; // �Լ������� �迭
	//for (int i = 0; i < 4; i++)
	//	printf("%d\n", p[i](10, 5));


	//int a = 10, b = 5;
	//int ret = temp(add, a, b);
	//printf("%d a�� b�� ��\n", ret);


	//void *p;
	//char ch = 'A';
	//p = &ch;
	//printf("%c\n", *(char *)p);

	//int i = 123;
	//p = &i;
	//printf("%d\n", *(int *)p);
	//
	//char arr[] = "abcde";
	//p = arr;
	//printf("%s\n", (char *)p);

	//printf("%c %c %c\n", *(char *)p, *((char *)p + 1), *((char *)p + 2));

	//printf("%c\n", *(((char *)p)++)); // ++ a
	//printf("%c\n", *(((char *)p)++));

	//void * parray[5][2] = { {add, "ADDITION"}, {sub, "SUBTRACTIOIN"}, {mul, "MULTIPLY"}, {div, "DIVIDE"}, {0,0} };
	//while(1)
	//{
	//	int input;
	//	printf("/*���� ���α׷�*/\n");
	//	for (int i = 0; i < 4; i++)
	//	{
	//		printf("%d. %s\n",i + 1 ,parray[i][1]);
	//	}
	//	printf("��ȣ���� : ");
	//	scanf("%d", &input);
	//	printf("����� : %d\n", ((myfp_t)parray[input - 1][0])(10,5));
	//	printf("����� : %d\n", ((int(*)(int, int))parray[input - 1][0])(10,5));
	//}

	// �ڽ��� �ּҸ� �Է¹޾Ƽ� ���´� �ּ��� ũ�⸸ŭ�� ���� �Ҵ��ϰ� ���� �� ���
	//char buffer[256] = { 1, };
	//gets(buffer);

	//int len = strlen(buffer);
	//char * heap = (char *)malloc(len + 1);
	//strcpy(heap, buffer);
	//printf("%s %x, %d\n",heap, heap, len);
	//free(heap);


	//FILE * fwp;
	//fwp = fopen("a.txt", "w");
	//fprintf(fwp, "%d %c\n", 1, 'A');
	//fclose(fwp);

	//int num;
	//char ch;	
	//FILE * frp;
	//frp = fopen("a.txt", "r");
	//fscanf(frp, "%d %c", &num, &ch);
	//printf("%d %c\n", num, ch);
	//fclose(frp);

	//FILE * fap;
	//fap = fopen("a.txt", "a");
	//fprintf(fap, "������");
	//fclose(fap);

	//char buffer[16];
	//frp = fopen("a.txt", "r");
	//fscanf(frp, "%d %c %s", &num, &ch, buffer);
	//printf("%d %c %s\n", num, ch, buffer);
	//fclose(frp);

	//FILE *wp, *rp;
	//rp = fopen("1.jpg", "rb");
	//wp = fopen("2.jpg", "wb");

	//// �Ϻ� �ݺ� ����
	//char buffer[100];
	//int completeByte = 0;
	//while (1)
	//{
	//	int cnt = fread(buffer, 100, 1, rp);
	//	if (cnt < 100)
	//	{
	//		if (feof(rp))
	//		{
	//			fwrite(buffer, sizeof(char), cnt, wp);
	//			completeByte += cnt;
	//			printf("%d Byte ����Ϸ�\n", completeByte);
	//		}
	//		else
	//			puts("�������");
	//		break;
	//	}
	//	fwrite(buffer, 100, 1, wp);
	//	completeByte += 100;
	//}
	//system("pause");
	//return 0;
	//
	//// ��ü ���� io.h 
	//int fileLen = _filelength(fileno(rp));
	//char * fileData = (char *)malloc(fileLen);
	//fread(fileData, fileLen, 1, rp);
	//if (fileLen != fwrite(fileData, fileLen, 1, wp))
	//	puts("�������");
	//free(fileData);
	//printf("%d Byte ����Ϸ�\n", fileLen);

	//fclose(rp);
	//fclose(wp);

	//int count;
	//printf("���ϴ� ������ ������ �Է��ϼ��� : ");
	//scanf("%d", &count);
	//getchar();
	//
	//char **p = (char **)malloc(sizeof(char *) * count);
	//
	//char temp[256];
	//for (int i = 0; i < count; i++)
	//{
	//	printf("%d ��° ����\n", i + 1);
	//	gets(temp);
	//	p[i] = (char *)malloc(strlen(temp) + 1);
	//	strcpy(p[i], temp);
	//	printf(p[i]);
	//}

	//for (int i = 0; i < count; i++)
	//{
	//	free(p[i]);
	//}
	//free(p);


	// ���� 5x5 
	// ������ ����
	// �Է½� ������ �ǿ��� x�� �ٲ�
	// ���� ���� �����ϰ� �ϳ� x
	srand((unsigned)time(NULL));

	int bingo[2][5][5] = { 0, };

	MakeBingo(bingo);
	int whoWin = 0;
	while (1)
	{
		PrintBingo(bingo);

		printf("bingo select : ");
		int input;
		scanf("%d", &input);

		int x, y;
		BingoSelect(bingo[0], input, &x, &y);
		if (WinCheck(bingo[0], x, y))
			break;

		int comX, comY;
		BingoSelect_Com(bingo[1], &comX, &comY);
		if (WinCheck(bingo[1], comX, comY))
		{
			whoWin = 1;
			break;
		}
	}
	PrintBingo(bingo);
	printf("PLAYER %s\n", whoWin ? "LOSE" : "WIN");


	if (1)
	{
		int a;
	}

	system("pause");
	return 0;
}