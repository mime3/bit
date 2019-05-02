#include "Stu.h"

Stu::Stu(string name, int num) : name(name), num(num)
{
}

Stu::Stu(const Stu & stu)
{
	name = stu.name;
	num = stu.num;
	iq = stu.iq;
	printf("복사생성자\n");
}


Stu::~Stu()
{
}

void Stu::Study(int tcnt)
{
	cout << "Stu : Study()" << endl;
}
