#include <iostream>
#include "ironman.h"

using namespace std;

int main()
{
	Soldier sd1("아이언맨", "철장갑", "초특급레이져");
	cout << sd1->Get() << endl;
	return 0;
}