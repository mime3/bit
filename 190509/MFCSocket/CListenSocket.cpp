#include "pch.h"
#include "CListenSocket.h"
#include "CClientSocket.h"

CListenSocket::CListenSocket()
{
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CClientSocket* client = new CClientSocket;
	if (Accept(*client))
	{
		client->SetListenSocket(this);
		m_ptrClientSokcet.AddTail(client);
	}
	else
	{
		delete client;
		AfxMessageBox(_T("ERROR : Failed to accept new Client!"));
	}

	CSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClinetSocket(CSocket* client)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrClientSokcet.Find(client);
	if (pos != NULL)
	{
		if (client != NULL)
		{
			client->ShutDown();
			client->Close();
		}
		m_ptrClientSokcet.RemoveAt(pos);
		delete client;
	}
}


void CListenSocket::SendChatDataAll(TCHAR * message)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrClientSokcet.GetHeadPosition();
	CClientSocket* client = NULL;

	while (pos != NULL)
	{
		client = (CClientSocket*)m_ptrClientSokcet.GetNext(pos);
		if (client != NULL)
		{
			client->Send(message, lstrlen(message) * 2);
		}
	}
}
