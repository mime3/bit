#include "UV.h"
#include <stdio.h>

int main()
{
	char nameBuffer[128];
	int stuBuffer;
	printf("�б���� �л����� �Է��Ͻÿ�\n�б��� : ");
	scanf_s("%s", nameBuffer, 128);
	printf("�л��� : ");
	scanf_s("%d", &stuBuffer);

	GradeHandler handler(nameBuffer, stuBuffer);

	while (1)
	{
		int input, input2;
		printf("\n1. �л�����\n2. ��������\n3. ����\n���� :: ");
		scanf_s("%d", &input);

		switch (input)
		{
		case 1:
		{
			printf("1 - 1. �л��߰�\n1 - 2. �л�����\n1 - 3. �л�����\n���� :: ");
			scanf_s("%d", &input2);
			if (input2 == 1)
			{
				if (handler.GetIndex() == handler.GetTop())
				{
					printf("�л� FULL\n");
					continue;
				}
				char nameBuffer[32] = { 0, };
				int age;
				printf("�л��߰�\n");
				printf("�л��� : ");
				scanf_s("%s", nameBuffer, 32);
				printf("���� : ");
				scanf_s("%d", &age);

				handler.AddStudent(nameBuffer, age);
				handler.SetIndex();
				printf("�л� �Է� �Ϸ�\n");
			}
			else if (input2 == 2)
			{
				char nameBuffer[32];
				int id;
				printf("�л�����\n");
				printf("�л��� : ");
				scanf_s("%s", nameBuffer, 32);
				nameBuffer[31] = 0;
				printf("�й� : ");
				scanf_s("%d", &id);

				if (handler.GetStudent()[id - 1].GetDeleted())
					continue;
				if (id <= 0 || handler.GetTop() < id)
					continue;
				if (strcmp(handler.GetStudent()[id - 1].GetName(), nameBuffer) == 0)
				{
					int age;
					printf("�� �л��� : ");
					scanf_s("%s", nameBuffer, 32);
					printf("�� ���� : ");
					scanf_s("%d", &age);
					handler.UpdateStudent(nameBuffer, age, id);
					printf("�л� ���� �Ϸ�\n");
				}
			}
			else if (input2 == 3)
			{
				char nameBuffer[32];
				int id;
				printf("�л�����\n");
				printf("�л��� : ");
				scanf_s("%s", nameBuffer, 32);
				nameBuffer[31] = 0;
				printf("�й� : ");
				scanf_s("%d", &id);
				handler.DeleteStudent(id);
				printf("�л� ���� �Ϸ�\n");
			}
			else
				continue;

			break;
		}
		case 2:
		{
			printf("2 - 1. �л�����Ʈ\n2 - 2. �����߰�\n���� :: ");
			scanf_s("%d", &input2);
			if (input2 == 1)
			{
				handler.PrintStuList();
				for (int i = 0; i < handler.GetIndex(); i++)
				{
					handler.GetStudent()[i].PrintScore();
				}
			}
			else if (input2 == 2)
			{
				int id;
				printf("�й� : ");
				scanf_s("%d", &id);
				if (id <= 0 || handler.GetTop() < id)
					continue;

				if (handler.GetStudent()[id - 1].GetDeleted())
					continue;

				Student & student = handler.GetStudent()[id - 1];
				printf("%s �л�\n", student.GetName());

				int kor, eng, math;
				printf("���� ���� : ");
				scanf_s("%d", &kor);
				printf("���� ���� : ");
				scanf_s("%d", &eng);
				printf("���� ���� : ");
				scanf_s("%d", &math);

				student.AddSubjectScore(KOREAN, kor);
				student.AddSubjectScore(ENGLISH, eng);
				student.AddSubjectScore(MATH, math);
				handler.PrintStuList();
				student.PrintScore();
			}
			break;
		}
		case 3:
			goto EXIT;
		default:
			fflush(stdin);
			break;
		}
	}

	EXIT:
	return 0;
}