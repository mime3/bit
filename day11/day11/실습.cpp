#include <iostream>
#pragma warning (disable:4996)
#include <cstdio>
#include<cstring>
using namespace std;
class Engine
{
private:
	int horsepower;
	int getHP(void) const
	{
		return horsepower;
	}
public:
	Engine(int power)
	{
		if (120 > power || power > 290)
		{
			cout << "불가능한 파워입니다" << endl;
			horsepower = 0;
		}
		else
			horsepower = power;
	}
	Engine(Engine& copy) :horsepower(copy.horsepower)
	{
	}
	int getHorsepower(void) const
	{
		return getHP();
	}
	void showEngineInfo() const
	{
		int power = getHorsepower();
		if (power != 0)
			cout << power << endl;
	}
	~Engine()
	{
		cout << "base" << endl;
	}
};
class intercoolerEngine : public Engine
{
private:
	char* cooler;
public:
	intercoolerEngine(int hp, const char* col) :Engine(hp)
	{
		cooler = new char[strlen(col) + 1];
		strcpy(cooler, col);
	}
	intercoolerEngine(const intercoolerEngine& copy) :Engine(copy.getHorsepower())
	{
		cooler = new char[strlen(copy.cooler) + 1];
		strcpy(cooler, copy.cooler);
	}
	friend void viewcooler(intercoolerEngine& view);
	void showerICEngine()
	{
		showEngineInfo();
		//cout << viewcooler(*this) << endl;
		viewcooler(*this);
	}
	~intercoolerEngine()
	{
		delete[]cooler;
		cout << "deconstructor" << endl;
	}
};
void viewcooler(intercoolerEngine& view)
{
	cout << view.cooler << endl;
}
class turboEngine : public intercoolerEngine
{
private:
	char charger;
public:
	turboEngine(int eg, char *col, char type)
	 :intercoolerEngine(eg, col), charger(type)
 {

 }


 void showTEngineInfo() const
 {
	 showEngineInfo();
	 viewcooler(*(intercoolerEngine *)this);
 }

 void showturboEngineInfo() const
 {
	 cout << charger << endl;
 }

};
int main()
{
	Engine eng1(150);
	eng1.showEngineInfo();
	puts("");
	intercoolerEngine eng2(270, "물");
	eng2.showerICEngine();
	puts("");
	intercoolerEngine eng3 = eng2;
	eng3.showerICEngine();
	puts("");
	return 0;
}
