#pragma once
#include <Windows.h>

enum USER_TYPE : BYTE
{
	NONE,
	CITIZEN,
	POLICE,
	DOCTOR,
	MAFIA
};

struct MAFIA_DATA
{
	USER_TYPE	type;
	BYTE		life;
	bool		vote;
	int			voted;
};
