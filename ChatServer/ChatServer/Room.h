#pragma once
#include <map>
#include "Player.h"
#include "MafiaManager.h"

typedef struct ROOM
{
	int							roomNo;
	WCHAR						roomName[20];
	std::map<UINT, Player*>		userMap;
	MafiaManager				gameManager;

	void Init(int roomNo);
}Room;

