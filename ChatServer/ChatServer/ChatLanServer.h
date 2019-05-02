#pragma once
#include "LanServer.h"
#include "Player.h"
#include "Room.h"
#include "Message.h"
#include <map>
#include <unordered_map>

LPCWSTR LOG_FILENAME = L"Mafia";

using namespace std;
class ChatLanServer : public LanServer
{
	MemoryPoolTLS<PLAYER>			_memoryPoolPlayer;		// 플레이어 메모리풀
	MemoryPoolTLS<MESSAGE>			_memoryPoolMessage;		// 메시지 메모리풀
	unordered_map<__int64, PLAYER*>	_playerMap;				// 플레이어들을 저장할 MAP
	LF_Queue<MESSAGE*>				_messageQueue;			// 메시지를 담을 락프리 큐

	MemoryPoolTLS<ROOM>				_memoryPoolRoom;
	LF_Stack<int>					_roomNoStack;
	unordered_map<int, ROOM*>		_roomMap;

	UINT				_accountNoSeed = 1;
	HANDLE				_wakeUpEvent;						// 스레드를 깨울 이벤트객체
	HANDLE				_mafiaEvent;						// 마피아 게임 진행 유도 이벤트객체
	HANDLE				_updateThread;						// 컨텐츠 처리 스레드
	bool				_exitFlag;							// 종료 플래그 (미구현)

	LONG _LOGIN_PLAYER = 0;									// 디버그전용
	LONG _PACKET_TYPE_ERROR = 0;								// 디버그전용
	LONG _NOT_EXIST_PLAYER = 0;								// 디버그전용
	LONG _WRONG_MOVE = 0;									// 디버그전용
	LONG _WRONG_CHATLEN = 0;									// 디버그전용
	LONG _UPDATE_TPS = 0;									// 디버그전용
	ULONGLONG _UPDATE_TPS_TIME = GetTickCount64();									// 디버그전용


	/* 내부 멤버 함수 */
	static UINT WINAPI UpdateThread(LPVOID param);			// 업데이트 스레드
	static UINT WINAPI MafiaThread(LPVOID param);			// 업데이트 유도 스레드
	void PutMessageData(Message* message);					// 큐에 메시지 넣고 스레드 깨움
	bool GetMessageData(Message** message);					// 큐에서 메시지 꺼냄

	void NewPlayer(MESSAGE* message);						// 새 플레이어 생성
	void DeletePlayer(__int64 sessionID);					// 플레이어 삭제
	void UpdateGame();										// 마피아 게임 진행
	void PacketProc(MESSAGE* message);						// 패킷 파싱함수

	bool Login(__int64 sessionID, Packet* data);			// 로그인 처리함수
	bool RoomList(__int64 sessionID, Packet* data);
	bool RoomCreate(__int64 sessionID, Packet* data);
	bool RoomDestory(__int64 sessionID, Packet* data);
	bool RoomEnter(__int64 sessionID, Packet* data);
	bool RoomJoin(__int64 sessionID, Packet* data);
	bool RoomLeave(__int64 sessionID, Packet* data);
	bool Chat(__int64 sessionID, Packet* data);				// 채팅 처리함수
	bool GameStart(__int64 sessionID, Packet* data);
	bool Vote(__int64 sessionID, Packet* data);
	bool UseAbility(__int64 sessionID, Packet* data);

	void MakePacket_Res_Login(Packet* packet, LOGIN_CODE login, UINT accountNo);
	void MakePacket_Res_RoomList(Packet* packet, unordered_map<int, ROOM*> * roomMap);
	void MakePacket_Res_RoomCreate(Packet* packet, CREATE_CODE result, int roomNo, WORD roomNameLen, WCHAR * roomName);
	void MakePacket_Res_RoomDestory(Packet* packet, UINT roomNo);
	void MakePacket_Res_RoomEnter(Packet* packet, UINT accountNo, WCHAR * nickName);
	void MakePacket_Res_RoomJoin(Packet* packet);
	void MakePacket_Res_RoomLeave(Packet* packet, UINT accountNo);
	void MakePacket_Res_Chat(Packet* packet, UINT accountNo, WCHAR* nickName, WORD chatLen, WCHAR* chat);
	void MakePacket_Res_GameStart(Packet* packet);
	void MakePacket_Res_GameEnd(Packet* packet, WIN win);
	void MakePacket_Res_RoleNotify(Packet* packet);
	void MakePacket_Res_TimeChange(Packet* packet);
	void MakePacket_Res_VoteStart(Packet* packet);
	void MakePacket_Res_Vote(Packet* packet, VOTE_CODE resultCode);
	void MakePacket_Res_VoteEnd(Packet* packet);
	void MakePacket_Res_Die(Packet* packet, UINT accountNo);

	void BroadCastAll(Packet* packet);
	void BroadCastRoom(Packet* packet, int roomNo, bool live = false); // 플레이어 방에 브로드캐스트

public:
	ChatLanServer();
	~ChatLanServer();

	void Stop();
	void PrintInfo();

	// LanServer을(를) 통해 상속됨
	virtual void OnClientJoin(INT64 ClientID, Session* session) override;
	virtual void OnClientLeave(INT64 ClientID) override;
	virtual bool OnConnectionRequest(WCHAR* ClientIP, int Port) override;
	virtual void OnRecv(INT64 clientID, StreamBuffer* packet) override;
	virtual void OnSend(INT64 clientID, int sendSize) override;
	virtual void OnError(int errorCode, const WCHAR* errorMessage) override;

};

enum ERROR_CODE
{
	PACKET_TYPE_ERROR,
	NOT_EXIST_PLAYER,
	NOT_LOGIN,
	WRONG_ACCOUNT_NO,
	WRONG_CHATLEN,
	WRONG_ABILITY,
	VOTE_NOT_START,
	ALREADY_VOTE
};