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

	MemoryPoolTLS<User>				_memoryPoolUser;		// �÷��̾� �޸�Ǯ
	MemoryPoolTLS<MESSAGE>			_memoryPoolMessage;		// �޽��� �޸�Ǯ
	map<INT64, USER*>				_userMap;
	LF_Queue<MESSAGE*>				_messageQueue;			// �޽����� ���� ������ ť

	HANDLE							_wakeUpEvent;

	bool							_exitFlag;
	WORD							_loginUser = 0;

	LONG _LOGIN_PLAYER			= 0;						// ���������
	LONG _PACKET_TYPE_ERROR		= 0;						// ���������
	LONG _NOT_EXIST_PLAYER		= 0;						// ���������
	LONG _WRONG_MOVE			= 0;						// ���������
	LONG _WRONG_CHATLEN			= 0;						// ���������
	LONG _UPDATE_TPS			= 0;						// ���������
	ULONGLONG _UPDATE_TPS_TIME	= GetTickCount64();			// ���������


	void Login(INT64 sessionID, Packet* packet);
	void Chat(INT64 sessionID, Packet* packet);
	void PacketProc(MESSAGE* message);

	void MakePacket_Res_Login(Packet* packet, INT64 sessionID, WCHAR *nickName);
	void MakePacket_Res_Chat(Packet* packet, INT64 sessionID, WORD chatLen, WCHAR * chat);
	void MakePacket_Res_Join(Packet* packet, INT64 sessionID, WCHAR* nickName);
	void MakePacket_Res_Leave(Packet* packet, INT64 sessionID);

	void BroadCast(Packet * packet, INT64 sessionID, bool sendSession = true);

	void PutMessageData(Message* message);					// ť�� �޽��� �ְ� ������ ����
	bool GetMessageData(Message** message);					// ť���� �޽��� ����

	void NewPlayer(MESSAGE* message);						// �� �÷��̾� ����
	void DeletePlayer(__int64 sessionID);					// �÷��̾� ����

	static UINT WINAPI UpdateThread(LPVOID lpParam);

	// LanServer��(��) ���� ��ӵ�
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