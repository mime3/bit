#pragma once
#include <Windows.h>
#include "Mafia.h"

constexpr auto NICKNAME_LEN = 20;

typedef struct PLAYER
{
	INT64		sessionID;
	bool		loginFlag;
	UINT		accountNo;
	WCHAR		nickName[NICKNAME_LEN];
	int			roomNo;
	MAFIA_DATA	mafia;

	void GameInit();
	void Die();
	void UseAbility(UINT targetID);
}Player;

void PLAYER::GameInit()
{
	mafia.life = 1;
	mafia.type = NONE;
	mafia.vote = false;
}

void PLAYER::Die()
{
	mafia.life = 0;
}