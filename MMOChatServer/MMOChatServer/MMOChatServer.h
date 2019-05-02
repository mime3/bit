#pragma once
#include "MMOServer.h"
#include "MMOChatSession.h"
#include "Sector.h"

constexpr int MAX_SECTOR_X = 100;
constexpr int MAX_SECTOR_Y = 100;


class MMOChatServer : public MMOServer
{
private:
	MMOChatSession _userSession[MAX_SESSION];
	Sector _sector[MAX_SECTOR_Y][MAX_SECTOR_X];

	// accountNo로 MMOChatSession 찾는 함수
	MMOChatSession* FindSession(INT64 accountNo);

	// MMOServer을(를) 통해 상속됨
	virtual void OnAuth_Update() override;
	virtual void OnContents_Update() override;
public:
	MMOChatServer();
	~MMOChatServer();

	bool MoveSector(MMOChatSession* session, INT64 accountNo, WORD sectorX, WORD sectorY);
	void BroadCastSector(Packet* packet, WORD sectorX, WORD sectorY);
};