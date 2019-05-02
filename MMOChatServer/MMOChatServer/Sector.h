#pragma once
#include <Windows.h>
#include <vector>
#include <set>

typedef struct Sector
{
	std::vector<INT64> userVector;
	std::set<__int64> playerSet;
}SECTOR;
