#pragma once
#include "Level.h"
#include "Passenger.h"
#include "Airline.h"
enum WEATHER
{
	CLEAR,		// ����
	SLIGHTLY,	// ��������
	VERY,		// ��������
	MUDDY		// �帲
};

class ControlTower
{
	WEATHER wc;
};



class Airport : public LEVEL
{
	char* name;
	int level;
	ControlTower ct;

	Airline** al;
	int maxCapacity;
	int topCapacity;

	// LEVEL��(��) ���� ��ӵ�
	virtual void LevelUP() override;
};