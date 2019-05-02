#pragma once
//이름과 전번을 저장하는 tel 클래스(이름,전번)를 만들고
//
//tel클래스 객체를 20개 저장하는 배열을 멤버로 갖는
//telhandler 클래스가 있다.
//main함수
//telhandler 형 객체;
//
//[]연산자를 오버로딩하여
//
//객체명["김기백"] 를 출력하면 김기백의 789가 리턴되게 하시오
//
//이름   전번
/*
"배상우", 111
"소준영", 666
"손병국", 909
"고승희", 222
"구민교", 808
"김기백", 789
"김다희", 404
"박선애", 303
"박성경", 987
"신동열", 333
"이경수", 202
"조희은", 555
"황상진", 456
"강상헌", 654
"이호세", 777
"전하람", 101
"이승연", 999
"조민희", 123
"이인찬", 321
"지도현", 707
*/
class Telhandler;
typedef Telhandler telhandler;

class Tel
{
	const char* name = nullptr;
	int num = 0;
public:
	Tel() {}
	void Input(const char* name, int num)
	{
		this->name = name;
		this->num = num;
	}
	friend class Telhandler;
};

class Telhandler
{
	Tel  _stu[20];

public:
	Telhandler()
	{
		_stu[0].Input("배상우", 111);
		_stu[1].Input("소준영", 666);
		_stu[2].Input("손병국", 909);
		_stu[3].Input("고승희", 222);
		_stu[4].Input("구민교", 808);
		_stu[5].Input("김기백", 789);
		_stu[6].Input("김다희", 404);
		_stu[7].Input("박선애", 303);
		_stu[8].Input("박성경", 987);
		_stu[9].Input("신동열", 333);
		_stu[10].Input("이경수", 202);
		_stu[11].Input("조희은", 555);
		_stu[12].Input("황상진", 456);
		_stu[13].Input("강상헌", 654);
		_stu[14].Input("이호세", 777);
		_stu[15].Input("전하람", 101);
		_stu[16].Input("이승연", 999);
		_stu[17].Input("조민희", 123);
		_stu[18].Input("이인찬", 321);
		_stu[19].Input("지도현", 707);
	}				  
	int operator[](const char * name)
	{
		for (auto & stu : _stu)
		{
			if (strcmp(stu.name, name) == 0)
				return stu.num;
		}
		return -1;
	}
};