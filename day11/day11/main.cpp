#include <stdio.h>
#include <iostream>
using namespace std;

namespace mystd
{
	int a = 10;
	namespace mystdin
	{
		int a = 20;
	}
}

int a = 30;

class Num
{
	int aaa = 1;
	static int staaa;
public:
	int a;

	Num(int a) : a(a)
	{

	}

	void set_aaa(int aaa)
	{
		this->aaa = aaa;
	}
	int get_aaa() const
	{
		return aaa;
	}
	void st()
	{
		staaa = 1;
	}

};
int Num::staaa = 2;

#include "Car.h"
#include "Matrix.h"
#include "Vector.h"
#include "Engine.h"
#include "aaabbb.h"
#include <time.h>

int main()
{
	/*namespace myin = mystd::mystdin;
	Num ob(40);
	cout << mystd::a << endl;
	cout << mystd::mystdin::a << endl;
	cout << ::a << endl;
	cout << ob.a<< endl;
	cout << myin::a << endl;
	ob.st();
*/

	//Car c0;
	//Car c1(200);
	//Car c2(200, 30);
	//Car c3(200, 30, 40);
	//c0.View();
	//c1.View();
	//c2.View();
	//c3.View();

	//int** p2 = new int* [3];

	//p2[0] = new int[5];
	//p2[1] = new int[5];
	//p2[2] = new int[5];

	//delete p2[0];
	//delete p2[1];
	//delete p2[2];

	srand(time(NULL));
	//Martix m(5, 5);
	//m.SetRand();
	//m.Print();
	//int max = m.MaxPixel();
	//int x = m.Element(0, 0);
	//printf("%d %d", max, x);

	//Vector<int> vt;
	//vt.RandSet();
	//vt.View("vt");
	//Vector<int> vt2 = vt;
	//vt2 = vt;
	//vt2.View("vt2");
	//Vector<int> vt3(vt);
	//vt3.View("vt3");

	//Engine eng1(150);
	//InterCoolerEngine eng2(270, "π∞");
	//InterCoolerEngine eng3(eng2);
	//TurboEngine eng4(2900, "ø¿¿œ", 'B');

	//eng1.PrintData();
	//eng2.PrintData();
	//eng3.PrintData();
	//eng4.PrintData();

	BBB ob1(20);
	BBB ob2(ob1);
	BBB ob3 = ob1;
	BBB ob4(40);
	ob4 = ob1;
	std::cout << ob1.get_b() << std::endl;
	std::cout << ob4.get_b() << std::endl;
	return 0;
}


