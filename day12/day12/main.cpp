#include <stdio.h>	
#include <iostream>
#include "Number.h"

using namespace std;

class AAA
{
	int num;
	friend class smart;
public:
	AAA(int a) : num(a) {}
	void Set(int a) { num = a; }
	int Get() { return num; }
};

class smart
{
	AAA* p;
public:
	smart(AAA *p) :p(p){}
	~smart() { delete p; cout << "auto delete" << endl; }
	AAA& operator *() { return *p; }
	AAA* operator->() { return p; }
};

int main()
{
	Number a(10, 20);
	Number b(10, 20);

	if (operator ==(a, b))
		;
	if (a.operator==(b))
		cout << "true" << endl;
	else
		cout << "false" << endl;


	a = a + b;
	a = a + 5;
	Number c = 5 + b;

	cout << a.GetNumberfir() << a.GetNumbersec() << endl;


	AAA aaa(5);
	smart sma(new AAA(50));
	//*sma = 20;
	cout << (*sma).Get() << endl;
	sma->Set(10);
	return 0;
}