#include "Number.h"

Number::~Number()
{
}

bool operator==(const Number& compare1, const Number& compare2)
{
	//if (compare1.GetNumberfir() != compare2.GetNumberfir())
	if (compare1.fir != compare2.fir)
		return false;
	//if (compare1.GetNumbersec() != compare2.GetNumbersec())
	if (compare1.sec != compare2.sec)
		return false;
	return true;
}

Number operator+(const int ori, const Number& plus)
{
	return Number(ori + plus.fir, ori + plus.sec);
}
