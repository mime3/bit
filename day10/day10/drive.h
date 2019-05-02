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
	//���� �ӵ� ���
	void speed_engine();
	//�������� ���
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
	engine * history = nullptr;    //enigne������ history
public:
	//���� history�� �־�� �� engine�迭�� �����.(20r��)
	void make_history_size();
	//������� �Է¸�尡 �߻��Ҷ����� history�� �����Ѵ�.
	void update_history(int rkm, const char *rmode);
	//history������ ������ش�.
	void display_history();
};

class car
{
public:
	black_box * eye = nullptr; //���ȿ� ���ڽ� ����� ���� ���� �ְ� ���� �� �ִ�.
public:
	car();
	~car();
	//���� �ɼǿ� ���� �������·� ��� , ������ ��� �ɼ��ΰ�� ��������� ���ð����ϰڴ�.
	engine * sedan, *sports;
	//��ֹ��� ���� �ڵ� �����Ѵ� (���)
	void autoStop();
	//���Ŭ������ �����//��ڳ��ο� engine������ history�� 20�� �����. 
	void make_bbox();
};