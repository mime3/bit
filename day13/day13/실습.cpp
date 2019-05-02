#include "Product.h"


int main()
{
	ProductContainer pc(5);
	char tempName[128];
	strcpy_s(tempName, 128, "가나다");
	pc.AddProduct(tempName, 1000);
	strcpy_s(tempName, 128, "가나다라");
	pc.AddProduct(tempName, 2000);	
	strcpy_s(tempName, 128, "가나다라마");
	pc.AddProduct(tempName, 3000);	
	strcpy_s(tempName, 128, "가다마");
	pc.AddProduct(tempName, 4000);	
	strcpy_s(tempName, 128, "다라마나");
	pc.AddProduct(tempName, 5000);


	while (1)
	{
		printf("***** 상품 추가/수정/출력 *****\n \
메뉴 입력\n \
1)상품추가\n \
2)상품수정\n \
3)종합출력\n \
4)상품출력\n \
5)종료\n");

		int input;
		scanf_s("%d", &input);

		int valueBuffer;
		char nameBuffer[128];
		switch (input)
		{
		case 1:
		{
			printf("상품명 : ");
			scanf_s("%s", nameBuffer, 128);
			printf("상품가 : ");
			scanf_s("%d", &valueBuffer);
			if(pc.AddProduct(nameBuffer, valueBuffer))
				printf("상품 추가 완료\n");
			else
				printf("상품 추가 실패\n");
			break;
		}
		case 2:
		{
			int index;
			printf("상품 번호 : ");
			scanf_s("%d", &index);
			printf("상품명 : ");
			scanf_s("%s", nameBuffer, 128);
			printf("상품가 : ");
			scanf_s("%d", &valueBuffer);
			if (pc.ModProduct(index, nameBuffer, valueBuffer))
				printf("상품 수정 완료\n");
			else
				printf("상품 수정 실패\n");
			break;
		}
		case 3:
			pc.PrintProduct();
			break;
		case 4:
		{
			int index;
			printf("상품 번호 : ");
			scanf_s("%d", &index);
			pc.PrintProduct(index);
			break;
		}
		case 5:
			goto EXIT;
		default:
			break;
		}
	}

	EXIT:
	return 0;
}