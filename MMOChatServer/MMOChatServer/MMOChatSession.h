#pragma once
#include "MMOSession.h"
#include "Sector.h"

class MMOChatServer;

class MMOChatSession : public MMOSession 
{
private:
	short	_sectorX;
	short	_sectorY;

	INT64	_accountNo;
	WCHAR	_ID[20];
	WCHAR	_nickName[20];

	char	_sessionKey[64];
	
	void Login(Packet * packet);
	void MoveSector(Packet * packet);
	void Chat(Packet * packet);

	void MakePacket_Res_MoveSector(Packet* packet, INT64 accountNo, WORD sectorX, WORD sectorY);
	void MakePacket_Res_Chat(Packet* packet, INT64 accountNo, WORD sectorX, WORD sectorY);

	// MMOSession을(를) 통해 상속됨
	virtual void OnAuth_Packet(StreamBuffer * packet) override;
	virtual void OnAuth_ClientLeave(bool isExit) override;
	virtual void OnContents_Packet(StreamBuffer * packet) override;
	virtual void OnContents_ClientJoin() override;
	virtual void OnContents_ClientLeave() override;
	virtual void OnContents_ClientRelease() override;

	friend class MMOChatServer;
public:
	static MMOChatServer* _serverPointer;

public:
	MMOChatSession();
	~MMOChatSession();
};