#pragma once
#include <stdio.h>
#include <string.h>
#include <strsafe.h>
//EngineŬ������ ����(horsepower)�� ǥ���Ѵ�.
//������ 120���� 290������ ���� ������ �ִ�.
//������ �ִ� ������ ����ϴ� const�Լ��� �ִ�.
//�ش� const�Լ������� ���¿� ���������� �����Ҽ� ���� ��Ȳ�̴�.
//------------------------------------------ -
//intercoolerEngineŬ������ engine�� ����Ѵ�.
//���������� cooler�� ������ �ִ�.
//cooler��������* ���·� //"����" �Ǵ� "��" ���°� �Էµȴ�.
//�ش� ���°� �𷯸� ����ϴ� �Լ��� �ִ�.
//intercoolerEngineŬ������ ��ü�� �ڽŰ� ���� ��ü�� �״��
//�����ϴ� �ɷ��� �ִ�.
//------------------------------------------ -
//turboEngineŬ������ intercoolerEngineŬ������ ����Ѵ�.
//���������� turborchager�� ������ ������
//������ ������ A, B, C type�� ���ڰ� �Էµȴ�.
//--------------------------------------------
//1.engineŬ������ ��ü, 150���¿� �ش��ϴ�eng1��ü�� ����� ���
//2. intercoolerEngineŬ���� ��ü, 270���¿�  "��"�� ����ϴ� eng2��
//����� ���
//3. intercoolerEngine eng3�� eng2�� ���� ���� �� eng3���
//4. turboEngineŬ������ ��ü eng4 �� 290���¿� "����" �׸��� ������ 'B'
//Ÿ���� ����ϴ� ��ü�̴�.
//��¹���� ����, ���� + ����, ���� + ���� + ���� 3�������·� ��µȴ�.
//
//�ش� ��ü�� �Ҹ��ڿ� �ʿ��ϴٸ� delete �� �����Ͻÿ�

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
//���������� turborchager�� ������ ������
//������ ������ A, B, C type�� ���ڰ� �Էµȴ�.