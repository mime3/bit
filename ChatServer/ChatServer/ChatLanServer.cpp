#include "ChatLanServer.h"

void ChatLanServer::BroadCastAll(Packet* packet)
{
	auto iter = _playerMap.begin();
	auto iterEnd = _playerMap.end();

	for (; iter != iterEnd; ++iter)
	{
		SendPacket(iter->first, packet);
	}
}

void ChatLanServer::BroadCastRoom(Packet* packet, int roomNo, bool live)
{
	Room* room = _roomMap.find(roomNo)->second;
	auto iter = room->userMap.begin();
	auto iterEnd = room->userMap.end();

	for (; iter != iterEnd; ++iter)
	{
		if (live || iter->second->mafia.life == 0)
		{
			SendPacket(iter->second->sessionID, packet);
		}
	}
}

ChatLanServer::ChatLanServer()
{
	_exitFlag = false;
	_wakeUpEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	_mafiaEvent = CreateWaitableTimer(NULL, FALSE, NULL);
	LARGE_INTEGER li;
	li.QuadPart = 0;
	SetWaitableTimer(_mafiaEvent, &li, 5 * 1000, NULL, NULL, FALSE);
	_updateThread = (HANDLE)_beginthreadex(NULL, 0, UpdateThread, this, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	_mafiaThread = (HANDLE)_beginthreadex(NULL, 0, MafiaThread, this, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
}

ChatLanServer::~ChatLanServer()
{
	if (_exitFlag != true)
		Stop();
}

void ChatLanServer::Stop()
{
	LanServer::Stop();

	// 업데이트 스레드 종료
	_exitFlag = true;
	SetEvent(_wakeUpEvent);
	WaitForSingleObject(_updateThread, INFINITE);
	// 모든 플레이어 지우기
	auto iter = _playerMap.begin();
	auto iterEnd = _playerMap.end();
	for (; iter != iterEnd;)
	{
		_memoryPoolPlayer.Free(iter->second);
		iter = _playerMap.erase(iter);
	}
	// 모든 메시지 지우기
	INT64 qsize = _messageQueue.GetUseCount();
	while (qsize--)
	{
		Message* message = nullptr;
		if (!_messageQueue.DeQueue(&message))
			break;
		_memoryPoolMessage.Free(message);
	}
	CloseHandle(_wakeUpEvent);
	CloseHandle(_updateThread);
}

void ChatLanServer::PrintInfo()
{
	printf_s("[CHAT SERVER]\n");
	printf_s("----------------------------------------------------\n");
	printf_s("Session Count = %d\n", GetClientCount());
	printf_s("Packet Alloc Count = %d\n", StreamBuffer::_allocCount);

	printf_s("MSG Alloc Count = %d\n",_memoryPoolMessage._allocCount);
	printf_s("MSG Queue Count = %I64d\n", _messageQueue.GetUseCount());

	printf_s("Player Alloc Count = %d\n", _memoryPoolPlayer._allocCount);
	printf_s("Player MapSize = %I64d\n", _playerMap.size());

	printf_s("Accept Count = %I64d\n", _acceptCount);
	printf_s("Accept TPS = %d\n", _acceptTPS);
	printf_s("Update TPS = %d\n", _UPDATE_TPS);

	printf_s("----------------------------------------------------\n");

	InterlockedAdd((LONG*)& _acceptTPS, -_acceptTPS);
	InterlockedAdd((LONG*)& _UPDATE_TPS, -_UPDATE_TPS);


}

void ChatLanServer::OnClientJoin(INT64 ClientID, Session* session)
{
	if (_exitFlag)
		return;
	MESSAGE* message = _memoryPoolMessage.Alloc();
	message->type = MESSAGE::MESSAGE_TYPE::JOIN;
	message->sessionID = ClientID;
	PutMessageData(message);
}

void ChatLanServer::OnClientLeave(INT64 ClientID)
{
	if (_exitFlag)
		return;
	MESSAGE* message = _memoryPoolMessage.Alloc();
	message->type = MESSAGE::MESSAGE_TYPE::LEAVE;
	message->sessionID = ClientID;
	PutMessageData(message);
}

bool ChatLanServer::OnConnectionRequest(WCHAR* ClientIP, int Port)
{
	return true;
}

void ChatLanServer::OnRecv(INT64 clientID, StreamBuffer* packet)
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

void ChatLanServer::OnSend(INT64 clientID, int sendSize)
{
}

void ChatLanServer::OnError(int errorCode, const WCHAR* errorMessage)
{
	LOG(L"Server_OnError", LOG_WARNING, errorMessage);
}

UINT __stdcall ChatLanServer::UpdateThread(LPVOID param)
{
	ChatLanServer* _this = (ChatLanServer*)param;
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
		case MESSAGE::MESSAGE_TYPE::MAFIA:
			_this->UpdateGame();
			break;
		default:
			_this->OnError(PACKET_TYPE_ERROR, L"PacketType ERROR");
			break;
		}
		_this->_memoryPoolMessage.Free(message);

	}
	return 0;
}

UINT __stdcall ChatLanServer::MafiaThread(LPVOID param)
{
	ChatLanServer* _this = (ChatLanServer*)param;
	while (true)
	{
		WaitForSingleObject(_this->_mafiaEvent, INFINITE);
		if (_this->_exitFlag)
			break;
		Message* mafiaMessage = _this->_memoryPoolMessage.Alloc();
		mafiaMessage->type = MESSAGE::MESSAGE_TYPE::MAFIA;
		_this->PutMessageData(mafiaMessage);
	}
	return 0;
}

void ChatLanServer::PutMessageData(Message* message)
{
	_messageQueue.EnQueue(message);
	SetEvent(_wakeUpEvent);
}

bool ChatLanServer::GetMessageData(Message** message)
{
	return _messageQueue.DeQueue(message);
}

void ChatLanServer::NewPlayer(MESSAGE* message)
{
	PLAYER* newPlayer = _memoryPoolPlayer.Alloc();
	newPlayer->sessionID = message->sessionID;
	newPlayer->loginFlag = false;
	newPlayer->accountNo = 0;
	_playerMap.insert(pair<__int64, PLAYER*>(newPlayer->sessionID, newPlayer));
}

void ChatLanServer::DeletePlayer(__int64 sessionID)
{
	auto find = _playerMap.find(sessionID);
	if (find == _playerMap.end())
		return;
	PLAYER * player = find->second;
	if (player->loginFlag)
		InterlockedDecrement(&_LOGIN_PLAYER);
	_playerMap.erase(sessionID);

	// 방에서 삭제 필요
	if (player->roomNo != 0)
	{
		auto iterRoom = _roomMap.find(player->roomNo);
		iterRoom->second->userMap.erase(player->accountNo);
	}
	_memoryPoolPlayer.Free(player);
}

void ChatLanServer::UpdateGame()
{
	auto iterRoom = _roomMap.begin();
	auto iterRoomEnd = _roomMap.end();
	for (; iterRoom != iterRoomEnd; ++iterRoom)
	{
		MafiaManager * manager = &iterRoom->second->gameManager;

		ULONGLONG curTime = GetTickCount64();
		switch(manager->time)
		{
		case MafiaManager::TIME::INIT:
			manager->lastChangeTime = curTime;
			manager->time = MafiaManager::TIME::DAYTIME;
			break;
		case MafiaManager::TIME::DAYTIME:
			// 낮 -> 밤 변경시 실행코드
			if (curTime - manager->lastChangeTime > DAYTIME_PERIOD)
			{
				WIN win = manager->CheckEnd();
				if (win != NONE)
				{
					manager->started = false;

					Packet* endGame = PacketAlloc(LanServer);
					MakePacket_Res_GameEnd(endGame, win);
					BroadCastRoom(endGame, iterRoom->second->roomNo);
					PacketFree(endGame);
					break;
				}
				manager->lastChangeTime = curTime;
				manager->time = MafiaManager::TIME::NIGHTTIME;
				manager->StartVote(MafiaManager::TIME::NIGHTTIME);

				Packet* voteStart = PacketAlloc(LanServer);
				MakePacket_Res_VoteStart(voteStart, manager->time);
				BroadCastRoom(voteStart, iterRoom->second->roomNo, true);
				PacketFree(voteStart);
			}
			// 낮 동안 실행될 코드
			else
			{
				// 투표 시간 마감
				if (curTime - manager->voteStartTime > VOTETIME_PERIOD)
				{
					UINT select = 0;
					// 동률 없음
					if (manager->EndVote(&select))
					{
						UINT roomNo = (manager->userMap)[select]->roomNo;

						Packet* userDie = PacketAlloc(LanServer);
						MakePacket_Res_Die(userDie, select);
						BroadCastRoom(userDie, roomNo);
						PacketFree(userDie);
					}
				}
			}
			break;
		case MafiaManager::TIME::NIGHTTIME:
			// 밤 -> 낮 변경시 실행코드
			if (curTime - manager->lastChangeTime > NIGHTTIME_PERIOD)
			{
				WIN win = manager->CheckEnd();
				if (win != NONE)
				{
					manager->started = false;

					Packet* endGame = PacketAlloc(LanServer);
					MakePacket_Res_GameEnd(endGame, win);
					BroadCastRoom(endGame, iterRoom->second->roomNo);
					PacketFree(endGame);
					break;
				}
				manager->lastChangeTime = curTime;
				manager->time = MafiaManager::TIME::DAYTIME;
				manager->days++;
				manager->StartVote(MafiaManager::TIME::DAYTIME);

				Packet* voteStart = PacketAlloc(LanServer);
				MakePacket_Res_VoteStart(voteStart, manager->time);
				BroadCastRoom(voteStart, iterRoom->second->roomNo, true);
				PacketFree(voteStart);
			}
			// 밤 동안 실행될 코드 부분
			else
			{
				// 투표 마감
				if (curTime - manager->voteStartTime > VOTETIME_PERIOD)
				{
					UINT select = 0;
					// 동률 없음
					if (manager->EndVote(&select))
					{
						UINT roomNo = (manager->userMap)[select]->roomNo;

						Packet* userDie = PacketAlloc(LanServer);
						MakePacket_Res_Die(userDie, select);
						BroadCastRoom(userDie, roomNo);
						PacketFree(userDie);
					}
				}
			}
			break;
		}
	}
}

void ChatLanServer::PacketProc(MESSAGE* message)
{
	WORD type;
	*(message->data) >> type;
	switch (type)
	{
	case en_PACKET_CS_CHAT_REQ_LOGIN:
		Login(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_ROOM_LIST:
		RoomList(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_ROOM_CREATE:
		RoomCreate(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_ROOM_ENTER:
		RoomEnter(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_ROOM_LEAVE:
		RoomLeave(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_MESSAGE:
		Chat(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_MAFIA_START:
		GameStart(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_VOTE:
		Vote(message->sessionID, message->data);
		break;
	case en_PACKET_CS_CHAT_REQ_USE_ABILITY:
		UseAbility(message->sessionID, message->data);
		break;
	//case en_PACKET_CS_CHAT_REQ_HEARTBEAT:
	//	break;
	default:
		OnError(PACKET_TYPE_ERROR, L"Packet Type ERROR");
		break;
	}
}

bool ChatLanServer::Login(__int64 sessionID, Packet* data)
{
	// 무의미
	auto find = _playerMap.find(sessionID);
	if (find == _playerMap.end())
	{
		OnError(NOT_EXIST_PLAYER, L"Not_Exist_Player");
		return false;
	}
	PLAYER* player = find->second;

	WCHAR nickName[NICKNAME_LEN];
	data->Out(nickName, NICKNAME_LEN);

	//닉네임 확인
	LOGIN_CODE result = LOGIN_CODE::OK;
	auto iterPlayer = _playerMap.begin();
	auto iterPlayerEnd = _playerMap.end();
	for (; iterPlayer != iterPlayerEnd; ++iterPlayer)
	{
		Player* player = iterPlayer->second;
		if (wcscmp(player->nickName, nickName) == 0)
		{	
			result = LOGIN_CODE::ALREADY_NAME;
			break;
		}
	}

	if (result == LOGIN_CODE::OK)
	{
		player->loginFlag = true;
		player->accountNo = _accountNoSeed++;
	}

	InterlockedIncrement(&_LOGIN_PLAYER);

	StreamBuffer* Login_Res = PacketAlloc(LanServer);
	MakePacket_Res_Login(Login_Res, result, player->accountNo);
	SendPacket(sessionID, Login_Res);
	PacketFree(Login_Res);
	return true;
}

bool ChatLanServer::RoomList(__int64 sessionID, Packet* data)
{
	Packet* res_RoomList = PacketAlloc(LanServer);
	MakePacket_Res_RoomList(res_RoomList, &_roomMap);
	PacketFree(res_RoomList);
	return true;
}

bool ChatLanServer::RoomCreate(__int64 sessionID, Packet* data)
{
	WORD roomNameLen;
	*data >> roomNameLen;
	WCHAR * roomName = new WCHAR[roomNameLen / 2 + 1];
	data->Out(roomName, roomNameLen);
	roomName[roomNameLen / 2] = NULL;

	// 방 이름 중복 검색
	auto iterRoom = _roomMap.begin();
	auto iterRoomEnd = _roomMap.end();

	CREATE_CODE result = CREATE_CODE::OK;
	for (; iterRoom != iterRoomEnd; ++iterRoom)
	{
		Room* room = iterRoom->second;
		if (wcscmp(roomName, room->roomName) == 0)
		{
			result = CREATE_CODE::ALREADY_NAME;
			break;
		}
	}

	int roomNo = 0;
	if (result == CREATE_CODE::OK)
	{
		if (!_roomNoStack.Pop(&roomNo))
			result = CREATE_CODE::FULL;
	}

	if (result == CREATE_CODE::OK)
	{
		Room* newRoom = _memoryPoolRoom.Alloc();
		newRoom->Init(roomNo);
	}
	Packet* res_RoomCreate = PacketAlloc(LanServer);
	MakePacket_Res_RoomCreate(res_RoomCreate, result, roomNo, roomNameLen, roomName);
	BroadCastAll(res_RoomCreate);
	PacketFree(res_RoomCreate);

	delete[] roomName;
	if (result != CREATE_CODE::OK)
		return false;
	return true;
}

bool ChatLanServer::RoomDestory(Room * room)
{
	Packet* res_RoomDestory = PacketAlloc(LanServer);
	MakePacket_Res_RoomDestory(res_RoomDestory, room->roomNo);
	BroadCastAll(res_RoomDestory);
	PacketFree(res_RoomDestory);
	return true;
}

bool ChatLanServer::RoomEnter(__int64 sessionID, Packet* data)
{
	int roomNo;
	*data >> roomNo;

	ENTER_CODE resultCode = ENTER_CODE::OK;
	Player* player = _playerMap.find(sessionID)->second;
	auto iterRoom = _roomMap.find(roomNo);
	if (iterRoom == _roomMap.end())
		resultCode = ENTER_CODE::ROOMNO_ERROR;

	Packet* res_RoomEnter_Room = PacketAlloc(LanServer);
	MakePacket_Res_RoomEnter(res_RoomEnter_Room, resultCode, roomNo);

	if (resultCode == ENTER_CODE::OK)
	{
		Room* room = iterRoom->second;
		// 방에 원래 있던 유저목록 전송

		auto iterRoomUser = room->userMap.begin();
		auto iterRoomUserEnd = room->userMap.end();
		for (; iterRoomUser != iterRoomUserEnd; ++iterRoomUser)
		{
			Packet* res_RoomEnter = PacketAlloc(LanServer);
			MakePacket_Res_UserJoin(res_RoomEnter, iterRoomUser->second->accountNo, iterRoomUser->second->nickName);
			SendPacket(sessionID, res_RoomEnter);
			PacketFree(res_RoomEnter);
			SendPacket(iterRoomUser->second->sessionID, res_RoomEnter_Room);
		}
	}
	PacketFree(res_RoomEnter_Room);

	if (resultCode != ENTER_CODE::OK)
		return false;
	return true;
}

bool ChatLanServer::RoomJoin(__int64 sessionID, Packet* data)
{
	Packet* res_RoomJoin = PacketAlloc(LanServer);
	PacketFree(res_RoomJoin);
	return false;
}

bool ChatLanServer::RoomLeave(__int64 sessionID, Packet* data)
{
	Player* player = _playerMap.find(sessionID)->second;

	auto iterRoom = _roomMap.find(player->roomNo);
	if (iterRoom == _roomMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 존재하지 않는 방에서 나가기 시도", player->nickName);
		return false;
	}
	
	Room* room = iterRoom->second;
	auto iterRoomPlayer = room->userMap.find(player->accountNo);
	if (iterRoomPlayer == room->userMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 입장하지 않은 방에서 나가기 시도", player->nickName);
		return false;
	}

	// 다 나가면 방 파괴
	if (room->userMap.size() == 0)
	{
		RoomDestory(room);
		_roomMap.erase(room->roomNo);
		_memoryPoolRoom.Free(room);
	}

	Packet* res_RoomLeave = PacketAlloc(LanServer);
	MakePacket_Res_RoomLeave(res_RoomLeave, player->accountNo);
	BroadCastRoom(res_RoomLeave, player->roomNo);
	PacketFree(res_RoomLeave);
	return true;
}

bool ChatLanServer::Chat(__int64 sessionID, Packet* data)
{
	WORD chatLen;
	*data >> chatLen;
	WCHAR* chat = new WCHAR[chatLen + 1];
	data->Out(chat, chatLen);
	chat[chatLen] = 0;
	
	Player* player = _playerMap.find(sessionID)->second;
	if (player->roomNo == 0)
	{
		delete[] chat;
		return false;
	}

	auto iterRoom = _roomMap.find(player->roomNo);
	if (iterRoom == _roomMap.end())
	{	
		delete[] chat;
		return false;
	}
	
	Packet* res_Chat = PacketAlloc(LanServer);
	MakePacket_Res_Chat(res_Chat, player->accountNo, player->nickName, chatLen, chat);
	BroadCastRoom(res_Chat, player->roomNo);
	PacketFree(res_Chat);
	delete[] chat;

	return true;
}

bool ChatLanServer::GameStart(__int64 sessionID, Packet* data)
{
	Player* player = _playerMap.find(sessionID)->second;
	if (player->roomNo == 0)
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 방에 없는상태에서 게임 시작 시도", player->nickName);
		return false;
	}

	auto iterRoom = _roomMap.find(player->roomNo);
	if (iterRoom == _roomMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 존재하지 않는 방에서 게임 시작 시도", player->nickName);
		return false;
	}

	Room* room = iterRoom->second;
	auto iterPlayer = room->userMap.find(player->accountNo);
	if (iterPlayer == room->userMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 방 유저목록에 없는 상태로 게임 시작 시도", player->nickName);
		return false;
	}

	if (room->gameManager.started != false)
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 이미 시작한 게임을 시작 시도", player->nickName);
		return false;
	}
	room->gameManager.GameInit(&room->userMap);

	Packet* res_GameStart = PacketAlloc(LanServer);
	MakePacket_Res_GameStart(res_GameStart);
	BroadCastRoom(res_GameStart, player->roomNo);
	PacketFree(res_GameStart);
	return true;
}

bool ChatLanServer::Vote(__int64 sessionID, Packet* data)
{
	UINT candidateNo;
	*data >> candidateNo;

	Player* player = _playerMap.find(sessionID)->second;
	if(player->roomNo == 0)
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 방에 없는상태에서 투표 시도", player->nickName);
		return false;
	}

	auto iterRoom = _roomMap.find(player->roomNo);
	if (iterRoom == _roomMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 존재하지 않는 방에서 투표 시도", player->nickName);
		return false;
	}

	Room* room = iterRoom->second;
	auto iterPlayer = room->userMap.find(player->accountNo);
	if (iterPlayer == room->userMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 방 유저목록에 없는 상태로 투표 시도", player->nickName);
		return false;
	}

	auto target = _playerMap.find(candidateNo);
	if (target == _playerMap.end())
	{
		LOG(LOG_FILENAME, LOG_ERROR, L"%s 가 없는 상대에 투표 시도", player->nickName);
		return false;
	}

	VOTE_CODE resultCode = VOTE_CODE::SUCCESS;
	if (!room->gameManager.Vote(player, candidateNo))
		resultCode = VOTE_CODE::FAILURE;
	
	Packet* res_Vote = PacketAlloc(LanServer);
	MakePacket_Res_Vote(res_Vote, resultCode);
	PacketFree(res_Vote);
	return true;
}

bool ChatLanServer::UseAbility(__int64 sessionID, Packet* data)
{
	
	return true;
}

void ChatLanServer::MakePacket_Res_Login(Packet* packet, LOGIN_CODE login, UINT accountNo)
{
	*packet << login << accountNo;
}

void ChatLanServer::MakePacket_Res_RoomList(Packet* packet, unordered_map<int, ROOM*>* roomMap)
{
	WORD roomCount = (WORD)roomMap->size();
	*packet << en_PACKET_CS_CHAT_RES_ROOM_LIST << roomCount;
	auto iterRoom = roomMap->begin();
	auto iterRoomEnd = roomMap->end();
	for (; iterRoom != iterRoomEnd; ++iterRoom)
	{
		Room* room = iterRoom->second;
		WORD roomNameLen = (WORD)wcslen(room->roomName);
		*packet << room->roomNo << roomNameLen * 2;
		packet->In(room->roomName, roomNameLen);
		*packet << (BYTE)room->userMap.size();
		auto iterUser = room->userMap.begin();
		auto iterUserEnd = room->userMap.end();
		for (; iterUser != iterUserEnd; ++iterUser)
		{
			PLAYER* player = iterUser->second;
			packet->In(player->nickName, NICKNAME_LEN);
		}
	}
}

void ChatLanServer::MakePacket_Res_RoomCreate(Packet* packet, CREATE_CODE result, int roomNo, WORD roomNameLen, WCHAR* roomName)
{
	*packet << en_PACKET_CS_CHAT_RES_ROOM_CREATE << result;
	if (result == CREATE_CODE::OK)
	{
		*packet << roomNo << roomNameLen;
		packet->In(roomName, roomNameLen);
	}
}

void ChatLanServer::MakePacket_Res_RoomDestory(Packet* packet, int roomNo)
{
	*packet << en_PACKET_CS_CHAT_RES_ROOM_DESTORY << roomNo;
}

void ChatLanServer::MakePacket_Res_RoomEnter(Packet* packet, ENTER_CODE code, int roomNo)
{
	*packet << en_PACKET_CS_CHAT_RES_ROOM_ENTER << code;
	if (code == ENTER_CODE::OK)
	{
		Room* room = _roomMap.find(roomNo)->second;
		*packet << roomNo;
		WORD roomNameLen = (WORD)wcslen(room->roomName);
		*packet << roomNameLen * 2;
		packet->In(room->roomName, roomNameLen);
		BYTE userCount = (BYTE)room->userMap.size();
		*packet << userCount;
		auto iter = room->userMap.begin();
		auto iterEnd = room->userMap.end();
		for (; iter != iterEnd; ++iter)
		{
			PLAYER* player = iter->second;
			packet->In(player->nickName, NICKNAME_LEN);
			*packet << player->accountNo;
		}
	}
}

void ChatLanServer::MakePacket_Res_UserJoin(Packet* packet, UINT accountNo, WCHAR* nickName)
{
	*packet << en_PACKET_CS_CHAT_RES_USER_ENTER << accountNo;
	packet->In(nickName, NICKNAME_LEN);
}

void ChatLanServer::MakePacket_Res_RoomLeave(Packet* packet, UINT accountNo)
{
	*packet << en_PACKET_CS_CHAT_RES_ROOM_LEAVE << accountNo;
}

void ChatLanServer::MakePacket_Res_Chat(Packet* packet, UINT accountNo, WCHAR* nickName, WORD chatLen, WCHAR* chat)
{
	*packet << en_PACKET_CS_CHAT_RES_MESSAGE << accountNo;
	packet->In(nickName, NICKNAME_LEN);
	*packet << chatLen;
	packet->In(chat, chatLen / 2);
}

void ChatLanServer::MakePacket_Res_GameStart(Packet* packet)
{
}

void ChatLanServer::MakePacket_Res_GameEnd(Packet* packet, WIN win)
{
}

void ChatLanServer::MakePacket_Res_RoleNotify(Packet* packet)
{
}

void ChatLanServer::MakePacket_Res_TimeChange(Packet* packet)
{
}

void ChatLanServer::MakePacket_Res_VoteStart(Packet* packet, MafiaManager::TIME time)
{
}

void ChatLanServer::MakePacket_Res_Vote(Packet* packet, VOTE_CODE resultCode)
{
}

void ChatLanServer::MakePacket_Res_VoteEnd(Packet* packet)
{
}

void ChatLanServer::MakePacket_Res_Die(Packet* packet, UINT accountNo)
{
}
