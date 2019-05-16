#pragma once
#include "LanClient.h"

class CMFCChatClientApp;

class ChatClient : public LanClient
{
	CMFCChatClientApp*	_pointer;
	INT64				_serverID;
	bool				_connected;

	void PacketParse(Packet* packet);

	void Res_RoomList(Packet* packet);
	void Res_CreateRoom(Packet* packet);
	void Res_EnterRoom(Packet* packet);
	void Res_UserJoin(Packet* packet);
	void Res_LeaveRoom(Packet* packet);
	void Res_DestroyRoom(Packet* packet);
	void Res_Chat(Packet* packet);

	void MakePacket_Req_Login(Packet* packet);
	void MakePacket_Req_RoomList(Packet* packet);
	void MakePacket_Req_CreateRoom(Packet* packet);
	void MakePacket_Req_EnterRoom(Packet* packet);
	void MakePacket_Req_LeaveRoom(Packet* packet);
	void MakePacket_Req_Chat(Packet* packet);

	// LanClient을(를) 통해 상속됨
	virtual void OnClientJoin(INT64 ClientID, Session* session) override;
	virtual void OnClientLeave(INT64 ClientID) override;
	virtual bool OnConnectionRequest(char* ClientIP, int Port) override;
	virtual void OnRecv(INT64 clientID, StreamBuffer* packet) override;
	virtual void OnSend(INT64 clientID, int sendSize) override;
	virtual void OnError(int errorCode, const WCHAR* errorMessage) override;
	virtual void OnConnect(INT64 ClientID) override;

public:
	ChatClient(CMFCChatClientApp* pointer);
};