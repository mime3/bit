#include "Product.h"


int main()
{
	ProductContainer pc(5);
	char tempName[128];
	strcpy_s(tempName, 128, "������");
	pc.AddProduct(tempName, 1000);
	strcpy_s(tempName, 128, "�����ٶ�");
	pc.AddProduct(tempName, 2000);	
	strcpy_s(tempName, 128, "�����ٶ�");
	pc.AddProduct(tempName, 3000);	
	strcpy_s(tempName, 128, "���ٸ�");
	pc.AddProduct(tempName, 4000);	
	strcpy_s(tempName, 128, "�ٶ󸶳�");
	pc.AddProduct(tempName, 5000);


	while (1)
	{
		printf("***** ��ǰ �߰�/����/��� *****\n \
�޴� �Է�\n \
1)��ǰ�߰�\n \
2)��ǰ����\n \
3)�������\n \
4)��ǰ���\n \
5)����\n");

		int input;
		scanf_s("%d", &input);

		int valueBuffer;
		char nameBuffer[128];
		switch (input)
		{
		case 1:
		{
			printf("��ǰ�� : ");
			scanf_s("%s", nameBuffer, 128);
			printf("��ǰ�� : ");
			scanf_s("%d", &valueBuffer);
			if(pc.AddProduct(nameBuffer, valueBuffer))
				printf("��ǰ �߰� �Ϸ�\n");
			else
				printf("��ǰ �߰� ����\n");
			break;
		}
		case 2:
		{
			int index;
			printf("��ǰ ��ȣ : ");
			scanf_s("%d", &index);
			printf("��ǰ�� : ");
			scanf_s("%s", nameBuffer, 128);
			printf("��ǰ�� : ");
			scanf_s("%d", &valueBuffer);
			if (pc.ModProduct(index, nameBuffer, valueBuffer))
				printf("��ǰ ���� �Ϸ�\n");
			else
				printf("��ǰ ���� ����\n");
			break;
		}
		case 3:
			pc.PrintProduct();
			break;
		case 4:
		{
			int index;
			printf("��ǰ ��ȣ : ");
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