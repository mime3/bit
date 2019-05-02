#include "pch.h"
#include "MMOChatSession.h"
#include "MMOChatServer.h"

void MMOChatSession::Login(Packet * packet)
{
	_authToContentsFlag = true;
}

void MMOChatSession::MoveSector(Packet * packet)
{
	INT64 accountNo;
	WORD sectorX, sectorY;

	*packet >> accountNo >> sectorX >> sectorY;
	// vector에서 이동
	_serverPointer->MoveSector(this, accountNo, sectorX, sectorY);
	Packet* res_MoveSector = PacketAlloc(MMOServer);
	MakePacket_Res_MoveSector(res_MoveSector, accountNo, sectorX, sectorY);
	SendPacket(res_MoveSector);
	PacketFree(res_MoveSector);
}

void MMOChatSession::Chat(Packet * packet)
{
	INT64 accountNo;
	WORD chatLen;

	*packet >> accountNo >> chatLen;
	WCHAR* chat = new WCHAR[chatLen];
	
	Packet* res_Chat = PacketAlloc(MMOServer);
	MakePacket_Res_Chat(res_Chat, accountNo, _sectorX, _sectorY);
	_serverPointer->BroadCastSector(res_Chat, _sectorX, _sectorY);
	PacketFree(res_Chat);
	delete chat;
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
	case en_PACKET_CS_CHAT_REQ_LOGIN:
		Login(packet->sessionID, packet->data);
		break;
	case en_PACKET_CS_CHAT_REQ_SECTOR_MOVE:
		MoveSector(packet->sessionID, packet->data);
		break;
	case en_PACKET_CS_CHAT_REQ_MESSAGE:
		Chat(packet->sessionID, packet->data);
		break;
	case en_PACKET_CS_CHAT_REQ_HEARTBEAT:
		break;
	default:
		OnError(PACKET_TYPE_ERROR, L"Packet Type ERROR");
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

MMOChatServer* MMOChatSession::_serverPointer = nullptr;