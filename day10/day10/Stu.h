#pragma once

#include <iostream>
#include <string>

using namespace std;

class Stu
{
	string name;
	int num;
	int iq;
public:
	Stu(string name, int num);
	Stu(const Stu & stu);
	~Stu();
	void Study(int tcnt);
};

