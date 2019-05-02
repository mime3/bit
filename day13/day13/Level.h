#pragma once
enum LEVEL_LIST
{
	BRONZE,
	SILVER,
	GOLD
};

struct LEVEL
{
	virtual void LevelUP() = 0;
};