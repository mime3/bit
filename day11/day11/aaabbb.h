#pragma once

class AAA
{
	int a;
public:
	AAA() :a(0){}
	AAA(int a) : a(a){}
	void set_a(int data)
	{
		a = data;
	}
	int get_a() const
	{
		return a;
	}
};

class BBB : public AAA
{
	int b;
public:
	BBB(int b) : AAA(), b(b){}
	BBB(const BBB& copy) : AAA(copy.get_a()) {}

	void operator=(const BBB& copy)
	{
		AAA::operator=(copy);
		b = copy.b;
	}
	void set_b(int data)
	{
		b = data;
	}
	int get_b() const
	{
		return b;
	}
};