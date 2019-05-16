#pragma once
#include <map>
#include <stack>
#include <random>
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include "Player.h"

using namespace std;

constexpr auto DAYTIME_PERIOD = 40 * 60 * 1000;
constexpr auto NIGHTTIME_PERIOD = 10 * 60 * 1000;
constexpr auto VOTETIME_PERIOD = 10 * 60 * 1000;

typedef USER_TYPE WIN;

struct MafiaManager
{
	enum TIME
	{
		INIT,
		DAYTIME,
		NIGHTTIME
	};

	bool				started;
	map<UINT, Player*>	userMap;
	map<UINT, Player*>	citizenUserMap;
	map<UINT, Player*>	mafiaUserMap;

	TIME				time;
	int					days;
	bool				voteStarted;

	TIME				voteType;
	map<UINT, UINT>		voteData;	// ID, ÅõÇ¥¼ö Pair
	ULONGLONG			lastChangeTime;
	ULONGLONG			voteStartTime;


	bool GameInit(map<UINT, Player*>* userMap);
	bool StartVote(TIME time);
	bool Vote(Player* voter, UINT candidateNo);
	bool UseAbilitiy();

	bool EndVote(UINT* player);
	WIN CheckEnd();
};

