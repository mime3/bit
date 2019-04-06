#pragma once
#include "MMOServer.h"
#include "MMOChatSession.h"
#include "Sector.h"

class MMOChatServer : public MMOServer
{
private:
	MMOChatSession _userSession[MAX_SESSION];
	Sector _sector[MAX_SECTOR_Y][MAX_SECTOR_X];


	// MMOServer을(를) 통해 상속됨
	virtual void OnAuth_Update() override;
	virtual void OnContents_Update() override;

public:
	MMOChatServer();
	~MMOChatServer();


};