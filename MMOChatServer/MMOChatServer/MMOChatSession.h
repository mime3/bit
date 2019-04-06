#pragma once
#include "MMOSession.h"
#include "Sector.h"

class MMOChatSession : public MMOSession 
{
private:
	short	_sectorX;
	short	_sectorY;
	
	void Login(Packet * packet);
	void MoveSector(Packet * packet);
	void Chat(Packet * packet);

	// MMOSession��(��) ���� ��ӵ�
	virtual void OnAuth_Packet(StreamBuffer * packet) override;
	virtual void OnAuth_ClientLeave(bool isExit) override;
	virtual void OnContents_Packet(StreamBuffer * packet) override;
	virtual void OnContents_ClientJoin() override;
	virtual void OnContents_ClientLeave() override;
	virtual void OnContents_ClientRelease() override;

public:
	MMOChatSession();
	~MMOChatSession();
};