#pragma once

#include<iostream>
#include<cstdlib>
using namespace std; //using 지시문
using std::cout;     //using 선언

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
		cout << "밥먹다" << endl;
	}
};

class kok : public Food
{
public:
	void eat()
	{
		cout << "국먹다" << endl;
	}
};

class kim : public Food
{
public:
	void eat()
	{
		cout << "김먹다" << endl;
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


//main함수에서 밥,국,김을 따로따로 불편하게 먹고 있습니다.
//Wrap 클래스를 만들어 
//main함수에서 brunch객체를 사용하여 wrap 객체에 담긴
//밥,국, 김을 한번에 먹으시오.

class Brunch 
{
public:
	void eattherice(bob &rb) { rb.eat(); }
	void eatthesoup(kok &rok) { rok.eat(); }
	void eatthekim(kim &rk) { rk.eat(); }
	void eat(Food & food) { food.eat(); }
	void eat(Wrap & wrap) { wrap.eat(); }
};