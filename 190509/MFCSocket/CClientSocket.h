#pragma once
#include <afxsock.h>
class CClientSocket : public CSocket
{
public:
	CAsyncSocket* m_listenSocket;

public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetListenSocket(CAsyncSocket* listenSocket);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

