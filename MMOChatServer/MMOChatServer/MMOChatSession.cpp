#include "pch.h"
#include "MMOChatSession.h"

void MMOChatSession::Login(Packet * packet)
{
	_authToContentsFlag = true;
}

void MMOChatSession::MoveSector(Packet * packet)
{
}

void MMOChatSession::Chat(Packet * packet)
{
}

void MMOChatSession::OnAuth_Packet(StreamBuffer * packet)
{
	WORD type;
	*packet >> type;

	switch (type)
	{
	default:
		break;
	}
}

void MMOChatSession::OnAuth_ClientLeave(bool isExit)
{
	if (isExit)
		_logOutFlag = true;
}

void MMOChatSession::OnContents_Packet(StreamBuffer * packet)
{
	WORD type;
	*packet >> type;

	switch (type)
	{
	default:
		break;
	}
}

void MMOChatSession::OnContents_ClientJoin()
{
	_sectorX = rand() % MAX_SECTOR_X;
	_sectorY = rand() % MAX_SECTOR_Y;
}

void MMOChatSession::OnContents_ClientLeave()
{
	_logOutFlag = true;
}

void MMOChatSession::OnContents_ClientRelease()
{

}

MMOChatSession::MMOChatSession()
{
}

MMOChatSession::~MMOChatSession()
{
}
