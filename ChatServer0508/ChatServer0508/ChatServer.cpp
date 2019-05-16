#include "pch.h"
#include "ChatServer.h"
#include "../Common/Protocol.h"
#include "ChatServer0508Dlg.h"

void ChatServer::BroadCast(Packet* packet, INT64 sessionID, bool sendSession)
{
	auto iter = _userMap.begin();
	auto iterEnd = _userMap.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->logined == false)
			continue;
		if (iter->first == sessionID && !sendSession)
			continue;
		SendPacket(iter->first, packet);
	}
}

void ChatServer::PutMessageData(Message* message)
{
	_messageQueue.EnQueue(message);
	SetEvent(_wakeUpEvent);
}

bool ChatServer::GetMessageData(Message** message)
{
	return _messageQueue.DeQueue_UnSafe(message);
}

void ChatServer::NewPlayer(MESSAGE* message)
{
	User* newUser = new User;
	newUser->logined = false;
	newUser->sessionID = message->sessionID;
	newUser->nickname[0] = 0;
	_userMap.insert(make_pair(message->sessionID, newUser));

	WCHAR userSize[16];
	swprintf_s(userSize, 16, L"%d", _userMap.size());
	_dlgPointer->UserSize.SetWindowTextW(userSize);
}

void ChatServer::DeletePlayer(__int64 sessionID)
{
	auto iter = _userMap.find(sessionID);

	int index = _dlgPointer->List_User.FindString(0, iter->second->nickname);
	_dlgPointer->List_User.DeleteString(index);

	delete iter->second;
	_userMap.erase(iter);
	_loginUser--;


	Packet* leave = PacketAlloc(LanServer);
	MakePacket_Res_Leave(leave, sessionID);
	BroadCast(leave, sessionID, false);
	PacketFree(leave);

	WCHAR userSize[16];
	swprintf_s(userSize, 16, L"%d", _userMap.size());
	_dlgPointer->UserSize.SetWindowTextW(userSize);
}

UINT __stdcall ChatServer::UpdateThread(LPVOID lpParam)
{
	ChatServer* _this = (ChatServer*)lpParam;
	while (true)
	{
		Message* message = nullptr;
		if (!_this->GetMessageData(&message))
		{
			// 문제발생가능
			if (_this->_exitFlag)
				break;
			WaitForSingleObject(_this->_wakeUpEvent, INFINITE);
			continue;
		}
		long tps = InterlockedIncrement((LONG*)& _this->_UPDATE_TPS);

		switch (message->type)
		{
		case MESSAGE::MESSAGE_TYPE::JOIN:
			_this->NewPlayer(message);
			break;
		case MESSAGE::MESSAGE_TYPE::LEAVE:
			_this->DeletePlayer(message->sessionID);
			break;
		case MESSAGE::MESSAGE_TYPE::PACKET:
			_this->PacketProc(message);
			PacketFree(message->data);
			break;
		//case MESSAGE::MESSAGE_TYPE::MAFIA:
		//	_this->UpdateGame();
		//	break;
		default:
			//_this->OnError(PACKET_TYPE_ERROR, L"PacketType ERROR");
			break;
		}
		_this->_memoryPoolMessage.Free(message);

	}
	return 0;
}

void ChatServer::OnClientJoin(INT64 ClientID, Session* session)
{
	if (_exitFlag)
		return;
	MESSAGE* message = _memoryPoolMessage.Alloc();
	message->type = MESSAGE::MESSAGE_TYPE::JOIN;
	message->sessionID = ClientID;
	PutMessageData(message);
}

void ChatServer::OnClientLeave(INT64 ClientID)
{
	if (_exitFlag)
		return;
	MESSAGE* message = _memoryPoolMessage.Alloc();
	message->type = MESSAGE::MESSAGE_TYPE::LEAVE;
	message->sessionID = ClientID;
	PutMessageData(message);
}

bool ChatServer::OnConnectionRequest(WCHAR* ClientIP, int Port)
{
	return true;
}

void ChatServer::OnRecv(INT64 clientID, StreamBuffer* packet)
{
	if (_exitFlag)
		return;

	Packet* messageData = PacketAlloc(LanServer);
	memcpy_s(messageData->GetBuffer(), messageData->GetSize(), packet->GetBuffer(), packet->GetUseSize());
	messageData->MoveEndIndex(packet->GetUseSize());

	MESSAGE* message = _memoryPoolMessage.Alloc();
	message->type = MESSAGE::MESSAGE_TYPE::PACKET;
	message->sessionID = clientID;
	message->data = messageData;
	PutMessageData(message);
}

void ChatServer::OnSend(INT64 clientID, int sendSize)
{
}

void ChatServer::OnError(int errorCode, const WCHAR* errorMessage)
{
}

ChatServer::ChatServer(CChatServer0508Dlg* dlgPointer) : _dlgPointer(dlgPointer)
{
}

void ChatServer::Start()
{
	LanServer::Start();
	_updateThread = (HANDLE)_beginthreadex(NULL, NULL, UpdateThread, this, NULL, NULL);
	_dlgPointer->OnOff.SetWindowTextW(L"ON");
}

void ChatServer::Login(INT64 sessionID, Packet* packet)
{
	_userMap[sessionID]->logined = true;
	packet->Out(_userMap[sessionID]->nickname, NICKNAME_LEN);
	Packet* res_Login = PacketAlloc(LanServer);
	MakePacket_Res_Login(res_Login, sessionID, _userMap[sessionID]->nickname);
	SendPacket(sessionID, res_Login);
	PacketFree(res_Login);

	_loginUser++;
	CString temp;
	temp.Format(_T("%s"), _userMap[sessionID]->nickname);
	_dlgPointer->List_User.AddString(temp);

	Packet* res_Join = PacketAlloc(LanServer);
	MakePacket_Res_Join(res_Join, sessionID, _userMap[sessionID]->nickname);
	BroadCast(res_Join, sessionID, false);
	PacketFree(res_Join);
}

void ChatServer::Chat(INT64 sessionID, Packet* packet)
{
	WORD chatLen;
	*packet >> chatLen;

	WCHAR* chat = new WCHAR[chatLen / 2];
	packet->Out(chat, chatLen / 2);

	Packet* res_Chat = PacketAlloc(LanServer);
	MakePacket_Res_Chat(res_Chat, sessionID, chatLen, chat);
	BroadCast(res_Chat, sessionID);
	PacketFree(res_Chat);

	delete[] chat;
}

void ChatServer::PacketProc(MESSAGE* message)
{
	WORD type;
	*(message->data) >> type;
	switch (type)
	{
	case LOGIN:
		Login(message->sessionID, message->data);
		break;
	case CHAT:
		Chat(message->sessionID, message->data);
		break;
	default:
		break;
	}
}

void ChatServer::MakePacket_Res_Login(Packet* packet, INT64 sessionID, WCHAR* nickName)
{
	*packet << PACKET_PROTOCOL::LOGIN << sessionID;
	packet->In(nickName, NICKNAME_LEN);
	*packet << _loginUser;

	auto iter = _userMap.begin();
	auto iterEnd = _userMap.end();
	for (;iter != iterEnd; ++iter)
	{
		if (iter->second->logined == false)
			continue;
		if (iter->first == sessionID)
			continue;
		*packet << iter->second->sessionID;
		packet->In(iter->second->nickname, NICKNAME_LEN);
	}
}

void ChatServer::MakePacket_Res_Chat(Packet* packet, INT64 sessionID, WORD chatLen, WCHAR* chat)
{
	*packet << PACKET_PROTOCOL::CHAT << sessionID << chatLen ;
	packet->In(chat, chatLen / 2);
}

void ChatServer::MakePacket_Res_Join(Packet* packet, INT64 sessionID, WCHAR* nickName)
{
	*packet << PACKET_PROTOCOL::JOIN << sessionID;
	packet->In(nickName, NICKNAME_LEN);
}

void ChatServer::MakePacket_Res_Leave(Packet* packet, INT64 sessionID)
{
	*packet << PACKET_PROTOCOL::LEAVE << sessionID;
}
