#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void swap1(int *pa, int *pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void swap2(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void swap(int * &pa, int * &pb)
{
	int * temp = pa;
	pa = pb;
	pb = temp;
}

//struct Number
//{
//	int fst;
//	int snd;
//};
//
//Number & NumberAdd(Number &a, Number &b)
//{
//	return *new Number{a.fst + b.fst, a.snd + b.snd};
//}

int & func1(int &ra)
{
	ra += 10;
	return ra;
}

int func2(int &ra)
{
	ra += 10;
	return ra;
}
#include "Stu.h"
#include "Number.h"

struct shallow
{
	int key;
	const char *p;
};

struct deep
{
	int key;
	const char p[10];
};


#include "Wrap.h"
#include "drive.h"

int main()
{
	//int a = 10;
	//int b = 5;
	//
	//swap1(&a, &b);
	//cout << a << ' ' << b << endl;
	//swap2(a, b);
	//cout << a << ' ' << b << endl;
	//
	//int * pa = &a;
	//int * pb = &b;
	//cout << pa << ' ' << pb << endl;
	//cout << *pa << ' ' << *pb << endl;
	//
	//swap(pa, pb);
	//cout << pa << ' ' << pb << endl;
	//cout << *pa << ' ' << *pb << endl;

	//Number * pa = new Number;
	//Number * pb = new Number;
	//pa->fst = 1;
	//pa->snd = 2;
	//pb->fst = 10;
	//pb->snd = 20;
	//Number &rpa = NumberAdd(*pa, *pb);
	//cout << rpa.fst << ' ' << rpa.snd << endl;
	//delete pa;
	//delete pb;
	//delete &rpa;

	//const int a = 10;
	//const int * p = &a;
	//const int *(&rp) = p;
	//cout << *p << ' ' << *rp << endl;


	//int a = 10;
	//int &rb = func1(a);
	//rb += 10;
	//cout << a << endl;
	//a = 10;
	//int rc = func1(a);
	//cout << a << endl;
	//a = 10;
	//int rd = func2(a);
	//cout << rd << endl;
	//a = 10;
	//const int & re = func2(a);
	//cout << re << endl;

	//Stu * stu = new Stu(20);
	//stu->Study(200);
	//delete stu;
	//Number oba;
	//Number obb(10);
	//obb.view();

	//shallow a = { 10, "AAA" }, b;
	//shallow c = { 20, "CCC" }, d;

	//b = a;
	//d = c;

	//Stu s1("홍길동", 10);
	//Stu s2(s1);



	//Number a, b, c;
	//a.DisplayAndRead("A =");
	//b.DisplayAndRead("B =");
	//c.addition(a, b);
	//a.printData("  A  = ");
	//b.printData("  B  = ");
	//c.printData(" A+B = ");

	Brunch bb;
	Wrap wrap;
	bob ob;
	kok ok;
	kim im;

	bb.eattherice(ob);
	bb.eatthesoup(ok);
	bb.eatthekim(im);

	bb.eat(wrap);

	bb.eat(ob);
	bb.eat(ok);
	bb.eat(im);


	car c;
	c.make_bbox();
	while (1)
	{
		printf("원하는 주행모드 선택\n");
		printf("------------------------\n");
		printf("[e]co 연비주행\n");
		printf("[s]ports 과속주행\n");
		printf("[h]istroy\n");
		printf("블박 %s\n", c.eye != nullptr ? "ON" : "OFF");
		printf("------------------------\n");
		
		engine * eng = nullptr;
		char mode;
		cin >> &mode;
		if (mode == 'e')
		{
			printf("에코모드 주행\n");
			eng = c.sedan;
		}
		else if (mode == 's')
		{
			printf("과속모드 주행\n");
			eng = c.sports;
		}
		else if (mode == 'h')
		{
			c.eye->display_history();
			continue;
		}
		else
			continue;
		printf("속도 입력 : ");
		int km;
		scanf_s("%d", &km);

		eng->set_km(km);
		eng->set_mode(mode);
		c.eye->update_history(km, &mode);
		c.autoStop();
	}


	getchar();
	return 0;
}

