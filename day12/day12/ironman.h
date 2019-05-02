#pragma once
#include <iostream>

//soldier �̸��� ���̾�� sdName[]�� ���̾���� �Է�
//glove  �̸��� ö�尩 gvName[]�� ö�尩�� �Է�
//weapon �̸��� ��Ư�޷������̴�.wpName[]�� ��Ư�޷����� �Էµȴ�.
//
//
//soldier�� glove�� ������ ������ glove�� weapon�� ������ �ִ�.
//�ᱹ ���̾���� ö�尩�� �� ���¿��� ��Ư�޷������� ���� �ִ� ��Ȳ�̴�.
//
//soldier�� �ִ� -> �����ڸ� �����ε��Ͽ� �Ͽ� ���̾� ���� ��Ư�޷�������
//����ϵ��� �����Ͻÿ�.
//
//int main()
//{
// soldier sd1("���̾��", "ö�尩", "��Ư�޷�����");
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