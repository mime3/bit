#pragma once
#include <iostream>
using namespace std;
constexpr auto HISTORY_SIZE = 20;

class engine
{
private:
	int km = 0;
	char mode = 0;
public:
	//모드와 속도 출력
	void speed_engine();
	//엔진정지 출력
	void stop_engine();
	void set_km(int rkm) { km = rkm; }
	void set_mode(char rmode) { mode = rmode; }
	int get_km() { return km; }
	char get_mode() { return mode; }

	void operator = (engine & eng)
	{
		km = eng.km;
		mode = eng.mode;
	}

};

class black_box
{
private:
	engine * history = nullptr;    //enigne형태의 history
public:
	//실제 history로 넣어야 할 engine배열을 만든다.(20rㅐ)
	void make_history_size();
	//사용자의 입력모드가 발생할때마다 history를 누적한다.
	void update_history(int rkm, const char *rmode);
	//history내역을 출력해준다.
	void display_history();
};

class car
{
public:
	black_box * eye = nullptr; //차안에 블랙박스 기능을 넣을 수도 있고 뺄수 도 있다.
public:
	car();
	~car();
	//차의 옵션에 따라 세단형태로 출발 , 스포츠 모드 옵션인경우 스포츠모드 선택가능하겠다.
	engine * sedan, *sports;
	//장애물을 보고 자동 정지한다 (출력)
	void autoStop();
	//블박클래스를 만들고//블박내부에 engine형태의 history를 20개 만든다. 
	void make_bbox();
};