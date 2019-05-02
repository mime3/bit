#include "UV.h"
#include <stdio.h>

int main()
{
	char nameBuffer[128];
	int stuBuffer;
	printf("학교명과 학생수를 입력하시오\n학교명 : ");
	scanf_s("%s", nameBuffer, 128);
	printf("학생수 : ");
	scanf_s("%d", &stuBuffer);

	GradeHandler handler(nameBuffer, stuBuffer);

	while (1)
	{
		int input, input2;
		printf("\n1. 학생관리\n2. 성적관리\n3. 종료\n선택 :: ");
		scanf_s("%d", &input);

		switch (input)
		{
		case 1:
		{
			printf("1 - 1. 학생추가\n1 - 2. 학생수정\n1 - 3. 학생삭제\n선택 :: ");
			scanf_s("%d", &input2);
			if (input2 == 1)
			{
				if (handler.GetIndex() == handler.GetTop())
				{
					printf("학생 FULL\n");
					continue;
				}
				char nameBuffer[32] = { 0, };
				int age;
				printf("학생추가\n");
				printf("학생명 : ");
				scanf_s("%s", nameBuffer, 32);
				printf("나이 : ");
				scanf_s("%d", &age);

				handler.AddStudent(nameBuffer, age);
				handler.SetIndex();
				printf("학생 입력 완료\n");
			}
			else if (input2 == 2)
			{
				char nameBuffer[32];
				int id;
				printf("학생수정\n");
				printf("학생명 : ");
				scanf_s("%s", nameBuffer, 32);
				nameBuffer[31] = 0;
				printf("학번 : ");
				scanf_s("%d", &id);

				if (handler.GetStudent()[id - 1].GetDeleted())
					continue;
				if (id <= 0 || handler.GetTop() < id)
					continue;
				if (strcmp(handler.GetStudent()[id - 1].GetName(), nameBuffer) == 0)
				{
					int age;
					printf("새 학생명 : ");
					scanf_s("%s", nameBuffer, 32);
					printf("새 나이 : ");
					scanf_s("%d", &age);
					handler.UpdateStudent(nameBuffer, age, id);
					printf("학생 수정 완료\n");
				}
			}
			else if (input2 == 3)
			{
				char nameBuffer[32];
				int id;
				printf("학생삭제\n");
				printf("학생명 : ");
				scanf_s("%s", nameBuffer, 32);
				nameBuffer[31] = 0;
				printf("학번 : ");
				scanf_s("%d", &id);
				handler.DeleteStudent(id);
				printf("학생 삭제 완료\n");
			}
			else
				continue;

			break;
		}
		case 2:
		{
			printf("2 - 1. 학생리스트\n2 - 2. 성적추가\n선택 :: ");
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
				printf("학번 : ");
				scanf_s("%d", &id);
				if (id <= 0 || handler.GetTop() < id)
					continue;

				if (handler.GetStudent()[id - 1].GetDeleted())
					continue;

				Student & student = handler.GetStudent()[id - 1];
				printf("%s 학생\n", student.GetName());

				int kor, eng, math;
				printf("국어 점수 : ");
				scanf_s("%d", &kor);
				printf("영어 점수 : ");
				scanf_s("%d", &eng);
				printf("수학 점수 : ");
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