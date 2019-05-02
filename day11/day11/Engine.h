#pragma once
#include <stdio.h>
#include <string.h>
#include <strsafe.h>
//Engine클래스는 마력(horsepower)을 표시한다.
//마력은 120에서 290마력을 값을 가질수 있다.
//가지고 있는 마력을 출력하는 const함수가 있다.
//해당 const함수에서는 마력에 직접적으로 접근할수 없는 상황이다.
//------------------------------------------ -
//intercoolerEngine클래스는 engine를 상속한다.
//내부적으로 cooler를 가지고 있다.
//cooler의종류는* 형태로 //"오일" 또는 "물" 형태가 입력된다.
//해당 마력과 쿨러를 출력하는 함수가 있다.
//intercoolerEngine클래스의 객체는 자신과 같은 객체를 그대로
//복사하는 능력이 있다.
//------------------------------------------ -
//turboEngine클래스는 intercoolerEngine클래스를 상속한다.
//내부적으로 turborchager를 가지고 있으며
//차저의 종류는 A, B, C type의 문자가 입력된다.
//--------------------------------------------
//1.engine클래스의 객체, 150마력에 해당하는eng1객체를 만들고 출력
//2. intercoolerEngine클래스 객체, 270마력에  "물"을 사용하는 eng2를
//만들고 출력
//3. intercoolerEngine eng3를 eng2로 부터 복사 후 eng3출력
//4. turboEngine클래스의 객체 eng4 는 290마력에 "오일" 그리고 차저는 'B'
//타입을 사용하는 객체이다.
//출력방법은 마력, 마력 + 오일, 마력 + 오일 + 차저 3가지형태로 출력된다.
//
//해당 객체에 소멸자에 필요하다면 delete 를 구현하시오

class Engine
{
	enum HORSERPOWER
	{
		HORSE_MIN = 120,
		HORSE_MAX = 290
	};
	int _horsePower;

public:
	Engine(int horsePower);
	int GetHorsePower() const;
	virtual void PrintData() const;
};

class InterCoolerEngine : public Engine
{
	char* _cooler;
public:
	InterCoolerEngine(int horsePower, const char * cooler);
	InterCoolerEngine(InterCoolerEngine& copy);
	~InterCoolerEngine();
	void PrintData() const;
	char* GetCooler() const;
};

class TurboEngine : public InterCoolerEngine
{
	char _turborChager;
public:
	TurboEngine(int horsePower, const char* coolerType, const char turborType);
	void PrintData() const;
};
//내부적으로 turborchager를 가지고 있으며
//차저의 종류는 A, B, C type의 문자가 입력된다.