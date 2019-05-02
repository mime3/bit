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
	MMOChatSession::_serverPointer = this;
}

MMOChatServer::~MMOChatServer()
{
}

bool MMOChatServer::MoveSector(MMOChatSession* session, INT64 accountNo, WORD sectorX, WORD sectorY)
{
	MMOChatSession* player = session;
	if (player->_accountNo != accountNo)
		return false;

	WORD newSectorX, newSectorY;
	auto iterUser = _sector[sectorY][sectorX].playerSet.find(accountNo);
	if (iterUser == _sector[sectorY][sectorX].playerSet.end())
		return false;
	
	if (sectorX < 0 || MAX_SECTOR_X - 1 < sectorX)
	{
		//OnError(WRONG_MOVE_SECTOR_X, L"Wrong_Move_Sector_X");
		return false;
	}
	if (sectorY < 0 || MAX_SECTOR_Y - 1 < sectorY)
	{
		//OnError(WRONG_MOVE_SECTOR_Y, L"Wrong_Move_Sector_Y");
		return false;
	}

	player->_sectorX = sectorX;
	player->_sectorY = sectorY;
	_sector[sectorY][sectorX].playerSet.insert(player->_sessionID);

	Packet* res_MoveSector = PacketAlloc(MMOServer);
	MakePacket_Res_MoveSector(res_MoveSector, );

	PacketFree(res_MoveSector);
	



	return false;
}

void MMOChatServer::BroadCastSector(Packet* packet, WORD sectorX, WORD sectorY)
{
}
