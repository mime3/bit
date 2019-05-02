// CChildThread.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication3.h"
#include "CChildThread.h"
#include "MainFrm.h"

// CChildThread

IMPLEMENT_DYNCREATE(CChildThread, CWinThread)

CChildThread::CChildThread()
{
}

CChildThread::~CChildThread()
{
}

BOOL CChildThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 프레임을 만들어 리소스와 함께 로드합니다.
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CChildThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	g_pUIThread = NULL;
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CChildThread, CWinThread)
END_MESSAGE_MAP()


// CChildThread 메시지 처리기
