#pragma once
class Number
{
	int fir;
	int sec;
public:
	Number(int f, int s) : fir(f), sec(s){}
	~Number();
	void SetNubmber(int data);
	int GetNumberfir() const { return fir; }
	int GetNumbersec() const { return sec; }
	bool operator==(Number & compare)
	{
		if (compare.fir != fir)
			return false;
		if (compare.sec != sec)
			return false;
		return true;
	}

	Number& operator +(const Number& plus)
	{
		fir += plus.fir;
		sec += plus.sec;
		return *this;
	}
	Number& operator +(const int plus)
	{
		fir += plus;
		sec += plus;
		return *this;
	}

	friend bool operator==(const Number& compare1, const Number& compare2);
	friend Number operator+(const int ori, const Number& plus);
};

