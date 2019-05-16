#pragma once
#include <afxsock.h>
class CListenSocket : public CSocket
{
public:
	CPtrList m_ptrClientSokcet;

public:
	CListenSocket();
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
	void CloseClinetSocket(CSocket* client);
	void SendChatDataAll(TCHAR* message);
};

