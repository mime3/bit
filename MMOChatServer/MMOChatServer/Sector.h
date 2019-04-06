#pragma once
#include <Windows.h>
#include <vector>

constexpr int MAX_SECTOR_X = 100;
constexpr int MAX_SECTOR_Y = 100;

typedef struct Sector
{
	std::vector<INT64> userVector;
}SECTOR;
