#pragma once
#include <map>
#include <stack>
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

	map<UINT, UINT>		voteData;
	ULONGLONG			lastChangeTime;
	ULONGLONG			voteStartTime;


	bool GameInit(map<UINT, Player*>* userMap);
	bool StartVote();
	bool Vote(Player* voter, UINT candidateNo);
	bool UseAbilitiy();

	bool EndVote(UINT* player);
	WIN CheckEnd();

	void BroadCastMessage(WCHAR* message, int len, bool live = false);
};

bool MafiaManager::GameInit(map<UINT, Player*>* userMap)
{
	this->userMap = *userMap;
	citizenUserMap.clear();
	mafiaUserMap.clear();
	started = true;
	time = INIT;
	days = 0;
	voteStarted = false;
	lastChangeTime = GetTickCount64();

	int mafia;

	if (this->userMap.size() < 5)
		mafia = 1;
	else if (this->userMap.size() < 9)
		mafia = 2;
	else
		mafia = 3;

	UINT size = this->userMap.size();

	bool* randArray = new bool[size];
	ZeroMemory(randArray, sizeof(bool) * size);

	int role = 2 + mafia - 1;
	while (role)
	{
		int select = rand() % size;
		auto iter = this->userMap.begin();
		while (select--)
			iter++;
		if (iter->second->mafia.type != NONE)
		{
			if(role < 2)
				iter->second->mafia.type = MAFIA;
			else if(role < 3)
				iter->second->mafia.type = POLICE;
			else
				iter->second->mafia.type = DOCTOR;
			role--;
		}
	}

	auto iter = this->userMap.begin();
	auto iterEnd = this->userMap.end();
	
	for (; iter != iterEnd; ++iter)
	{
		Player* player = iter->second;
		switch (player->mafia.type)
		{
		case NONE:
		case POLICE:
		case DOCTOR:
			citizenUserMap.insert(pair<UINT, Player*>(player->accountNo, player));
			break;
		case MAFIA:
			mafiaUserMap.insert(pair<UINT, Player*>(player->accountNo, player));
			break;
		default:
			break;
		}
	}
	delete[] randArray;

	return true;
}

bool MafiaManager::StartVote()
{
	if (voteStarted == true)
		return false;

	voteStarted = true;
	voteStartTime = GetTickCount64();
	return true;
}

inline bool MafiaManager::Vote(Player * voter, UINT candidateNo)
{
	if (voter->mafia.vote == true)
		return false;

	userMap[candidateNo]->mafia.voted++;

	if (!voteData.insert(pair<UINT, UINT>(candidateNo, 1)).second)
		voteData[candidateNo]++;

	return true;
}

inline bool MafiaManager::EndVote(UINT* player)
{
	UINT first = 0;
	UINT second = 0;
	UINT firstValue = 0;
	UINT secondValue = 0;

	auto iter = voteData.begin();
	auto iterEnd = voteData.end();
	for (; iter != iterEnd; ++iter)
	{
		if (firstValue < iter->second)
		{
			first = iter->first;
			firstValue = iter->second;
		}
		else if (secondValue < iter->second)
		{
			second = iter->first;
			secondValue = iter->second;
		}
	}
	voteStarted = false;
	if (firstValue == secondValue)
		return false;

	*player = first;
	return true;
}

inline WIN MafiaManager::CheckEnd()
{
	if (citizenUserMap.size() == mafiaUserMap.size())
		return MAFIA;

	if (mafiaUserMap.size() == 0)
		return CITIZEN;

	return NONE;
}
