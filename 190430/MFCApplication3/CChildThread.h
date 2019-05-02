#pragma once
#include "resource.h"
// CChildThread

class CChildThread : public CWinThread
{
	DECLARE_DYNCREATE(CChildThread)

protected:
	CChildThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CChildThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


