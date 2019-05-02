#pragma once
#include <iostream>
using namespace std;
class Number
{
	int fir;
	int sec;

public:
	Number();
	Number(int rfst);
	~Number();
	void view()
	{
		cout << fir << endl;
	}

	void DisplayAndRead(const char* msg) 
	{
		printf("  %s ", msg);
		scanf_s("%d %d", &fir, &sec);
	}

	void printData(const char* msg) 
	{
		printf("  %s %d + %d\n", msg, fir, sec);
	}

	void addition(Number & a, Number & b) 
	{
		fir = a.fir + b.fir;
		sec = a.sec + b.sec;
	}
};

