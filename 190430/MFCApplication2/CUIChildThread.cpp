#include "pch.h"
#include "CUIChildThread.h"


CUIChildThread::CUIChildThread()
{
}


CUIChildThread::~CUIChildThread()
{
}

BOOL CUIChildThread::InitInstance()
{
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;

	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR)
	return 0;
}
