#pragma once

#include<iostream>
#include<cstdlib>
using namespace std; //using ���ù�
using std::cout;     //using ����

class Food
{
public:
	virtual void eat() = 0;
};

class bob : public Food
{
public:
	void eat()
	{
		cout << "��Դ�" << endl;
	}
};

class kok : public Food
{
public:
	void eat()
	{
		cout << "���Դ�" << endl;
	}
};

class kim : public Food
{
public:
	void eat()
	{
		cout << "��Դ�" << endl;
	}
};

class Wrap
{
	bob b;
	kok k;
	kim k2;
public:
	//virtual void eat() = 0;
	void eat() 
	{ 
		b.eat(); 
		k.eat(); 
		k2.eat(); 
	};
};


//main�Լ����� ��,��,���� ���ε��� �����ϰ� �԰� �ֽ��ϴ�.
//Wrap Ŭ������ ����� 
//main�Լ����� brunch��ü�� ����Ͽ� wrap ��ü�� ���
//��,��, ���� �ѹ��� �����ÿ�.

class Brunch 
{
public:
	void eattherice(bob &rb) { rb.eat(); }
	void eatthesoup(kok &rok) { rok.eat(); }
	void eatthekim(kim &rk) { rk.eat(); }
	void eat(Food & food) { food.eat(); }
	void eat(Wrap & wrap) { wrap.eat(); }
};