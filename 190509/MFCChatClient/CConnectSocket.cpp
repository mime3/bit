// CConnectSocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFCChatClient.h"
#include "CConnectSocket.h"
#include "MFCChatClientDlg.h"


// CConnectSocket

CConnectSocket::CConnectSocket()
{
}

CConnectSocket::~CConnectSocket()
{
}


// CConnectSocket 멤버 함수


void CConnectSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR : Disconnect from server"));
	PostQuitMessage(0);
}


void CConnectSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	TCHAR buffer[1024] = { 0, };

	if (Receive(buffer, sizeof(buffer)) > 0)
	{
		CMFCChatClientDlg* main = (CMFCChatClientDlg*)AfxGetMainWnd();
		main->m_chatList.AddString(buffer);
		main->m_chatList.SetCurSel(main->m_chatList.GetCount() - 1);
	}

	CSocket::OnReceive(nErrorCode);
}
