#include "pch.h"
#include "CClientSocket.h"
#include "CListenSocket.h"
#include "MFCSocketDlg.h"


CClientSocket::CClientSocket()
{
	m_listenSocket = NULL;
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::SetListenSocket(CAsyncSocket* listenSocket)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	m_listenSocket = listenSocket;
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CSocket::OnClose(nErrorCode);

	CListenSocket* listenSocket = (CListenSocket*)m_listenSocket;
	listenSocket->CloseClinetSocket(this);
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString strTmp = _T("");
	CString strIP = _T("");
	UINT port = 0;
	TCHAR buffer[1024] = { 0, };

	GetPeerName(strIP, port);
	if (Receive(buffer, sizeof(buffer)) > 0)
	{
		CMFCSocketDlg * main = (CMFCSocketDlg*)AfxGetMainWnd();
		strTmp.Format(_T("[%s:%d] : %s"), strIP, port, buffer);
		main->m_chatList.AddString(strTmp);
		main->m_chatList.SetCurSel(main->m_chatList.GetCount() - 1);

		CListenSocket* serverSocket = (CListenSocket*)m_listenSocket;
		serverSocket->SendChatDataAll(buffer);
	}

	CSocket::OnReceive(nErrorCode);
}
