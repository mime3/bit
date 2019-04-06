#include "pch.h"
#include "MMOChatServer.h"

void MMOChatServer::OnAuth_Update()
{
}

void MMOChatServer::OnContents_Update()
{
}

MMOChatServer::MMOChatServer()
{
	for (int i = 0; i < MAX_SESSION; i++)
	{
		SetSessionArray(&_userSession[i], i);
	}
}

MMOChatServer::~MMOChatServer()
{
}
