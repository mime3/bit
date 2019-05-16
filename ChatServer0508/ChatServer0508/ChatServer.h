#pragma once
#pragma comment(lib, "MinLib")
#include "LanServer.h"
#include "Message.h"
#include <map>

class CChatServer0508Dlg;

constexpr auto NICKNAME_LEN = 20;

typedef struct USER
{
	bool logined;
	INT64 sessionID;
	WCHAR nickname[NICKNAME_LEN];
}User;

class ChatServer : LanServer
{
	CChatServer0508Dlg* _dlgPointer;
	HANDLE _updateThread;

	MemoryPoolTLS<User>				_memoryPoolUser;		// 플레이어 메모리풀
	MemoryPoolTLS<MESSAGE>			_memoryPoolMessage;		// 메시지 메모리풀
	map<INT64, USER*>				_userMap;
	LF_Queue<MESSAGE*>				_messageQueue;			// 메시지를 담을 락프리 큐

	HANDLE							_wakeUpEvent;

	bool							_exitFlag;
	WORD							_loginUser = 0;

	LONG _LOGIN_PLAYER			= 0;						// 디버그전용
	LONG _PACKET_TYPE_ERROR		= 0;						// 디버그전용
	LONG _NOT_EXIST_PLAYER		= 0;						// 디버그전용
	LONG _WRONG_MOVE			= 0;						// 디버그전용
	LONG _WRONG_CHATLEN			= 0;						// 디버그전용
	LONG _UPDATE_TPS			= 0;						// 디버그전용
	ULONGLONG _UPDATE_TPS_TIME	= GetTickCount64();			// 디버그전용


	void Login(INT64 sessionID, Packet* packet);
	void Chat(INT64 sessionID, Packet* packet);
	void PacketProc(MESSAGE* message);

	void MakePacket_Res_Login(Packet* packet, INT64 sessionID, WCHAR *nickName);
	void MakePacket_Res_Chat(Packet* packet, INT64 sessionID, WORD chatLen, WCHAR * chat);
	void MakePacket_Res_Join(Packet* packet, INT64 sessionID, WCHAR* nickName);
	void MakePacket_Res_Leave(Packet* packet, INT64 sessionID);

	void BroadCast(Packet * packet, INT64 sessionID, bool sendSession = true);

	void PutMessageData(Message* message);					// 큐에 메시지 넣고 스레드 깨움
	bool GetMessageData(Message** message);					// 큐에서 메시지 꺼냄

	void NewPlayer(MESSAGE* message);						// 새 플레이어 생성
	void DeletePlayer(__int64 sessionID);					// 플레이어 삭제

	static UINT WINAPI UpdateThread(LPVOID lpParam);

	// LanServer을(를) 통해 상속됨
	virtual void OnClientJoin(INT64 ClientID, Session* session) override;
	virtual void OnClientLeave(INT64 ClientID) override;
	virtual bool OnConnectionRequest(WCHAR* ClientIP, int Port) override;
	virtual void OnRecv(INT64 clientID, StreamBuffer* packet) override;
	virtual void OnSend(INT64 clientID, int sendSize) override;
	virtual void OnError(int errorCode, const WCHAR* errorMessage) override;


public:
	ChatServer(CChatServer0508Dlg* dlgPointer);

	void Start();

	friend class CChatServer0508Dlg;
};