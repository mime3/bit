#pragma once
#include "Extern.h"
#include "ChatLanClient.h"
// ChatDlg 대화 상자

class ChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChatDlg)
public:
	ChatLanClient* client;

public:
	ChatDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ChatDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
	CListBox ChatList;
	CListBox UserList;
	CEdit Edit_Chat;
	virtual BOOL OnInitDialog();
	CStatic Static_ID;
	CStatic Static_Nick;
	CStatic Static_Con;
};
