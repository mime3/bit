#pragma once
#include "Level.h"
#include "Airplane.h"

class Airline : public LEVEL
{
protected:
	char* name;
	int level;
	Airplane** ap;
	int maxCapacity;
	int topCapacity;
};

class DomesticAirline : public Airline
{
	// Airline��(��) ���� ��ӵ�
	virtual void LevelUP() override;
};

class InternationalAirline : public DomesticAirline
{

};