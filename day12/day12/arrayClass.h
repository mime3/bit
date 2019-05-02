#pragma once
//�̸��� ������ �����ϴ� tel Ŭ����(�̸�,����)�� �����
//
//telŬ���� ��ü�� 20�� �����ϴ� �迭�� ����� ����
//telhandler Ŭ������ �ִ�.
//main�Լ�
//telhandler �� ��ü;
//
//[]�����ڸ� �����ε��Ͽ�
//
//��ü��["����"] �� ����ϸ� ������ 789�� ���ϵǰ� �Ͻÿ�
//
//�̸�   ����
/*
"����", 111
"���ؿ�", 666
"�պ���", 909
"�����", 222
"���α�", 808
"����", 789
"�����", 404
"�ڼ���", 303
"�ڼ���", 987
"�ŵ���", 333
"�̰��", 202
"������", 555
"Ȳ����", 456
"������", 654
"��ȣ��", 777
"���϶�", 101
"�̽¿�", 999
"������", 123
"������", 321
"������", 707
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
		_stu[0].Input("����", 111);
		_stu[1].Input("���ؿ�", 666);
		_stu[2].Input("�պ���", 909);
		_stu[3].Input("�����", 222);
		_stu[4].Input("���α�", 808);
		_stu[5].Input("����", 789);
		_stu[6].Input("�����", 404);
		_stu[7].Input("�ڼ���", 303);
		_stu[8].Input("�ڼ���", 987);
		_stu[9].Input("�ŵ���", 333);
		_stu[10].Input("�̰��", 202);
		_stu[11].Input("������", 555);
		_stu[12].Input("Ȳ����", 456);
		_stu[13].Input("������", 654);
		_stu[14].Input("��ȣ��", 777);
		_stu[15].Input("���϶�", 101);
		_stu[16].Input("�̽¿�", 999);
		_stu[17].Input("������", 123);
		_stu[18].Input("������", 321);
		_stu[19].Input("������", 707);
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