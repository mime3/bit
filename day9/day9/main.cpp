#include <stdio.h>
//#define NDEBUG
#include <assert.h>
#include <string.h>
#include <windows.h>

constexpr auto KEYLEN = 10;
const char key[][KEYLEN] = { "Alice", "Bill", "Carol", "David", "Elvis", "Fred", "Gabriel",
	"Helen", "Isabel", "Jane", "Kuper", "Louic", "Mathilda", "Nadia", "Olive",
	"Pablo", "Queen", "Rambo", "Scarlet", "Trisha", "Umberto", "Vincent",
	"Wily", "Xxx", "Yuki", "Zorro" };


//1. 일반함수로 만들어 찾기
//2. 재귀함수로 만들어 찾기
//3. bsearch() - 라이브러리 함수로 찾기
//위 1, 2, 3번 함수로 Pablo가 몇번째 위치하는 지를 출력하시오

int serachKey(const char search[], const char keyarray[][10], int size)
{
	int index = size / 2;
	int minRange = 0;
	int maxRange = size;
	while (1)
	{
		if (maxRange - minRange <= 1)
			break;
		index = (maxRange + minRange + 1) / 2;
		int diff = strcmp(search, keyarray[index]);
		switch (diff)
		{
		case -1:
			maxRange = index;
			break;
		case 0:
			return index;
			break;
		case 1:
			minRange = index;
			break;
		default:
			break;
		}
	}
	return -1;
}


int serachKey2(const char search[], const char keyarray[][10], int maxRange, int minRange = 0)
{
	int index = (maxRange + minRange + 1) / 2;
	int diff = strcmp(search, keyarray[index]);
	int ret;
	if (diff == 0)
		return index;
	else if (diff == -1)
		ret = serachKey2(search, keyarray, index, minRange);
	else
		ret = serachKey2(search, keyarray, maxRange, index);
	return ret;
}

int compare(const void *arg1, const void *arg2)
{
	/* Compare all of both strings: */
	return strcmp((char*)arg1, (char*)arg2);
}

int main()
{
	//int x;
	//printf("x : ");
	//scanf_s("%d", &x);
	//assert(x > 0);
	//printf("%d \n", x);

	int index; 
	index = serachKey("Pablo", key, 26);
	if (index != -1)
	{
		printf("%d %s", index, key[index]);
		puts("");
	}

	index = serachKey2("Pablo", key, 26);
	if (index != -1)
	{
		printf("%d %s", index, key[index]);
		puts("");
	}

	char **result = (char **)bsearch("Pablo", key, sizeof(key) / KEYLEN, KEYLEN, compare);
	if(result)
		printf("%d %s\n", ((int)result - (int)key) / KEYLEN,  result);

	getchar();
	return 0;
}