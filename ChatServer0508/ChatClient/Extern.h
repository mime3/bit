#pragma once
#include <Windows.h>
#include <map>
struct User
{
	INT64 sessionID;
	WCHAR nickName[20];
};

extern WCHAR g_IP[20];
extern WCHAR g_nickName[20];
extern std::map<INT64, User*> g_userMap;