#pragma once
#include <iostream>

//soldier 이름은 아이언맨 sdName[]에 아이언맨이 입력
//glove  이름은 철장갑 gvName[]에 철장갑이 입력
//weapon 이름은 초특급레이져이다.wpName[]에 초특급레이져 입력된다.
//
//
//soldier는 glove를 가지고 있으면 glove는 weapon를 가지고 있다.
//결국 아이언맨은 철장갑을 낀 상태에서 초특급레이져를 쓰고 있는 상황이다.
//
//soldier에 있는 -> 연산자를 오버로딩하여 하여 아이언 맨이 초특급레이져를
//사용하도록 구현하시오.
//
//int main()
//{
// soldier sd1("아이언맨", "철장갑", "초특급레이져");
// cout << sd1->wpName << endl;
// return 0;
//}


class Weapon
{
	const char* wpName;
public:
	Weapon(const char* wpName) : wpName(wpName) {}
	const char* Get() { return wpName; }
	friend class Glove;
	friend class Soldier;
};

class Glove
{
	const char* gvName;
	Weapon* wp;

public:
	Glove(const char* gvName, const char* wpName)
		: gvName(gvName)
	{
		wp = new Weapon(wpName);
	}
	friend class Soldier;
};

class Soldier
{
	const char* sdName;
	Glove* gv;

public:
	Soldier(const char* sdName, const char* gvName, const char* wpName)
		: sdName(sdName)
	{
		gv = new Glove(gvName, wpName);
	}

	Weapon* operator -> ()
	{
		return (gv->wp);
	}
};