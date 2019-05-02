#pragma once
#include "Level.h"
#include "Passenger.h"
#include "Airline.h"
enum WEATHER
{
	CLEAR,		// 맑음
	SLIGHTLY,	// 구름조금
	VERY,		// 구름많음
	MUDDY		// 흐림
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

	// LEVEL을(를) 통해 상속됨
	virtual void LevelUP() override;
};