#pragma once
#pragma comment(lib, "MinLib")
#include "LanClient.h"

class ChatDlg;

class ChatLanClient : public LanClient
{
public:
	ChatDlg* _dlgPointer;
	INT64				_serverID;
	bool				_connected = false;

private:
	void Res_Login(Packet* packet);
	void Res_Chat(Packet* packet);
	void Res_Join(Packet* packet);
	void Res_Leave(Packet* packet);

	void PacketProc(Packet * packet);

	// LanClient을(를) 통해 상속됨
	virtual void OnClientJoin(INT64 ClientID, Session* session) override;
	virtual void OnClientLeave(INT64 ClientID) override;
	virtual bool OnConnectionRequest(char* ClientIP, int Port) override;
	virtual void OnRecv(INT64 clientID, StreamBuffer* packet) override;
	virtual void OnSend(INT64 clientID, int sendSize) override;
	virtual void OnError(int errorCode, const WCHAR* errorMessage) override;
	virtual void OnConnect(INT64 ClientID) override;

public:
	ChatLanClient(ChatDlg* dlgPointer);

	void MakePacket_Req_Login(Packet* packet);
	void MakePacket_Req_Chat(Packet* packet);

	bool SendPacket(Packet* packet);
};