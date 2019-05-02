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
	MemoryPoolTLS<PLAYER>			_memoryPoolPlayer;		// �÷��̾� �޸�Ǯ
	MemoryPoolTLS<MESSAGE>			_memoryPoolMessage;		// �޽��� �޸�Ǯ
	unordered_map<__int64, PLAYER*>	_playerMap;				// �÷��̾���� ������ MAP
	LF_Queue<MESSAGE*>				_messageQueue;			// �޽����� ���� ������ ť

	MemoryPoolTLS<ROOM>				_memoryPoolRoom;
	LF_Stack<int>					_roomNoStack;
	unordered_map<int, ROOM*>		_roomMap;

	UINT				_accountNoSeed = 1;
	HANDLE				_wakeUpEvent;						// �����带 ���� �̺�Ʈ��ü
	HANDLE				_mafiaEvent;						// ���Ǿ� ���� ���� ���� �̺�Ʈ��ü
	HANDLE				_updateThread;						// ������ ó�� ������
	bool				_exitFlag;							// ���� �÷��� (�̱���)

	LONG _LOGIN_PLAYER = 0;									// ���������
	LONG _PACKET_TYPE_ERROR = 0;								// ���������
	LONG _NOT_EXIST_PLAYER = 0;								// ���������
	LONG _WRONG_MOVE = 0;									// ���������
	LONG _WRONG_CHATLEN = 0;									// ���������
	LONG _UPDATE_TPS = 0;									// ���������
	ULONGLONG _UPDATE_TPS_TIME = GetTickCount64();									// ���������


	/* ���� ��� �Լ� */
	static UINT WINAPI UpdateThread(LPVOID param);			// ������Ʈ ������
	static UINT WINAPI MafiaThread(LPVOID param);			// ������Ʈ ���� ������
	void PutMessageData(Message* message);					// ť�� �޽��� �ְ� ������ ����
	bool GetMessageData(Message** message);					// ť���� �޽��� ����

	void NewPlayer(MESSAGE* message);						// �� �÷��̾� ����
	void DeletePlayer(__int64 sessionID);					// �÷��̾� ����
	void UpdateGame();										// ���Ǿ� ���� ����
	void PacketProc(MESSAGE* message);						// ��Ŷ �Ľ��Լ�

	bool Login(__int64 sessionID, Packet* data);			// �α��� ó���Լ�
	bool RoomList(__int64 sessionID, Packet* data);
	bool RoomCreate(__int64 sessionID, Packet* data);
	bool RoomDestory(__int64 sessionID, Packet* data);
	bool RoomEnter(__int64 sessionID, Packet* data);
	bool RoomJoin(__int64 sessionID, Packet* data);
	bool RoomLeave(__int64 sessionID, Packet* data);
	bool Chat(__int64 sessionID, Packet* data);				// ä�� ó���Լ�
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
	void BroadCastRoom(Packet* packet, int roomNo, bool live = false); // �÷��̾� �濡 ��ε�ĳ��Ʈ

public:
	ChatLanServer();
	~ChatLanServer();

	void Stop();
	void PrintInfo();

	// LanServer��(��) ���� ��ӵ�
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