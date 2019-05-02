#pragma once
#include "Level.h"
#include "Passenger.h"
class Airplane : public LEVEL
{
protected:
	int level;

	// LEVEL��(��) ���� ��ӵ�
public:
	virtual void LevelUP() override;
};

class Propeller : public Airplane
{
public:
	virtual void LevelUP() override;
};

class Sonic : public Airplane
{
public:
	virtual void LevelUP() override;
};

class SuperSonic : public Sonic
{
public:
	virtual void LevelUP() override;
};

class VerticalTOL : public Airplane
{
public:
	virtual void LevelUP() override;
};