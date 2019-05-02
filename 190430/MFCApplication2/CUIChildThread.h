#pragma once
class CUIChildThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIChildThread);

public:
	CUIChildThread();
	~CUIChildThread();

	BOOL InitInstance();
};

