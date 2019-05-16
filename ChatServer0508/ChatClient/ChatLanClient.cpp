#include "pch.h"
#include "ChatLanClient.h"
#include "ChatDlg.h"
#include "../Common/Protocol.h"

extern WCHAR g_IP[20];
extern WCHAR g_nickName[20];
extern std::map<INT64, User*> g_userMap;

void ChatLanClient::Res_Login(Packet* packet)
{
	User* my = new User;
	*packet >> my->sessionID;
	packet->Out(my->nickName, 20);

	CString temp;
	temp.Format(_T("My UserID : %I64d"), my->sessionID);
	_dlgPointer->Static_ID.SetWindowTextW(temp);
	temp.Format(_T("My NickName : %s"), my->nickName);
	_dlgPointer->Static_Nick.SetWindowTextW(temp);

	_dlgPointer->UserList.AddString(my->nickName);
	_dlgPointer->UserList.SetCurSel(_dlgPointer->UserList.GetCount() - 1);
	_dlgPointer->Edit_Chat.SetReadOnly(FALSE);
	g_userMap.insert(make_pair(my->sessionID, my));

	WORD user;
	*packet >> user;
	for (WORD i = 0; i < user; ++i)
	{
		User* newUser = new User;
		*packet >> newUser->sessionID;
		packet->Out(newUser->nickName, 20);
		g_userMap.insert(make_pair(newUser->sessionID, newUser));
		_dlgPointer->UserList.InsertString(-1, newUser->nickName);
	}
}

void ChatLanClient::Res_Chat(Packet* packet)
{
	INT64 userID;
	WORD chatLen;
	*packet >> userID >> chatLen;
	WCHAR* chat = new WCHAR[chatLen / 2 + 1];
	packet->Out(chat, chatLen / 2);
	chat[chatLen / 2] = 0;

	CString fullChat;
	fullChat.Format(_T("%s : %s"), g_userMap[userID]->nickName, chat);
	delete[] chat;

	int index = _dlgPointer->ChatList.AddString(fullChat);
	_dlgPointer->ChatList.SetCurSel(_dlgPointer->ChatList.GetCount() - 1);
}

void ChatLanClient::Res_Join(Packet* packet)
{
	User* newUser = new User;
	*packet >> newUser->sessionID;
	packet->Out(newUser->nickName, 20);
	g_userMap.insert(make_pair(newUser->sessionID, newUser));
	_dlgPointer->UserList.InsertString(-1, newUser->nickName);
}

void ChatLanClient::Res_Leave(Packet* packet)
{
	INT64 userID;
	*packet >> userID;

	auto iter = g_userMap.find(userID);
	if (iter != g_userMap.end())
	{
		int index = _dlgPointer->UserList.FindString(0, iter->second->nickName);
		_dlgPointer->UserList.DeleteString(index);
	}
}

void ChatLanClient::PacketProc(Packet* packet)
{
	WORD type;
	*packet >> type;
	switch (type)
	{
	case LOGIN:
		Res_Login(packet);
		break;
	case CHAT:
		Res_Chat(packet);
		break;
	case JOIN:
		Res_Join(packet);
		break;
	case LEAVE:
		Res_Leave(packet);
		break;
	default:
		break;
	}
}

void ChatLanClient::MakePacket_Req_Login(Packet* packet)
{
	*packet << PACKET_PROTOCOL::LOGIN;
	packet->In(g_nickName, 20);
}

void ChatLanClient::MakePacket_Req_Chat(Packet* packet)
{
	*packet << PACKET_PROTOCOL::CHAT;
	CString chat;
	_dlgPointer->Edit_Chat.GetWindowTextW(chat);
	*packet << (WORD)(chat.GetLength() * 2);
	packet->In(chat.GetBuffer(), chat.GetLength());
}

bool ChatLanClient::SendPacket(Packet* packet)
{
	return LanClient::SendPacket(_serverID, packet);
}

void ChatLanClient::OnClientJoin(INT64 ClientID, Session* session)
{
}

void ChatLanClient::OnClientLeave(INT64 ClientID)
{
	_dlgPointer->Edit_Chat.SetReadOnly();
	_dlgPointer->UserList.ResetContent();
	_dlgPointer->ChatList.ResetContent();
	AfxMessageBox(L"¿¬°á ²÷±è");
	//PostQuitMessage(0);
}

bool ChatLanClient::OnConnectionRequest(char* ClientIP, int Port)
{
	return true;
}

void ChatLanClient::OnRecv(INT64 clientID, StreamBuffer* packet)
{
	PacketProc(packet);
}

void ChatLanClient::OnSend(INT64 clientID, int sendSize)
{
}

void ChatLanClient::OnError(int errorCode, const WCHAR* errorMessage)
{
}

void ChatLanClient::OnConnect(INT64 ClientID)
{
	_serverID = ClientID;
	_connected = true;
	_dlgPointer->Static_Con.SetWindowTextW(L"");

	//_dlgPointer->UserList.InsertString(-1, g_nickName);
	_dlgPointer->Edit_Chat.SetReadOnly(FALSE);

	Packet* login = PacketAlloc(LanClient);
	MakePacket_Req_Login(login);
	SendPacket(login);
	PacketFree(login);
}

ChatLanClient::ChatLanClient(ChatDlg* dlgPointer) : _dlgPointer(dlgPointer)
{
	_serverID = 0;
}
