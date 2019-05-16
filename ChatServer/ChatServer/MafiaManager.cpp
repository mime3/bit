#include "MafiaManager.h"

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

	UINT size = (UINT)this->userMap.size();

	vector<PLAYER*> roleVector;
	roleVector.reserve(size);
	auto iter = this->userMap.begin();
	auto iterEnd = this->userMap.end();

	for (; iter != iterEnd; ++iter)
	{
		roleVector.push_back(iter->second);
	}

	random_device rd;
	mt19937 g(rd());
	shuffle(roleVector.begin(), roleVector.end(), g);
	// ¼ÅÇÃ ¿Ï·á

	auto iterRole = roleVector.begin();
	auto iterRoleEnd = roleVector.end();
	int role = mafia + 2;
	int roleSelect = 0;
	for (; iterRole != iterRoleEnd; ++iterRole)
	{
		if (roleSelect < role)
		{
			if (roleSelect == 0)
				(*iterRole)->mafia.type = DOCTOR;
			else if (roleSelect == 1)
				(*iterRole)->mafia.type = POLICE;
			else
				(*iterRole)->mafia.type = MAFIA;
			roleSelect++;
		}
		(*iterRole)->mafia.type = CITIZEN;
	}

	return true;
}

bool MafiaManager::StartVote(TIME time)
{
	if (voteStarted == true)
		return false;

	voteType = time;
	voteStarted = true;
	voteStartTime = GetTickCount64();

	auto iter = userMap.begin();
	auto iterEnd = userMap.end();
	for (; iter != iterEnd; ++iter)
	{
		iter->second->mafia.vote = false;
	}
	return true;
}

bool MafiaManager::Vote(Player * voter, UINT candidateNo)
{
	if (voter->mafia.vote == true)
		return false;

	userMap[candidateNo]->mafia.voted++;

	if (!voteData.insert(pair<UINT, UINT>(candidateNo, 1)).second)
		voteData[candidateNo]++;

	return true;
}

bool MafiaManager::EndVote(UINT * player)
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

WIN MafiaManager::CheckEnd()
{
	if (citizenUserMap.size() == mafiaUserMap.size())
		return MAFIA;

	if (mafiaUserMap.size() == 0)
		return CITIZEN;

	return NONE;
}
