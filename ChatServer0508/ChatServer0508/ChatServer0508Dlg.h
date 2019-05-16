
// ChatServer0508Dlg.h: 헤더 파일
//

#pragma once
#include "ChatServer.h"

// CChatServer0508Dlg 대화 상자
class CChatServer0508Dlg : public CDialogEx
{
	ChatServer chatServer;
// 생성입니다.
public:
	CChatServer0508Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSERVER0508_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic OnOff;
	CStatic UserSize;
	CListBox List_User;
	afx_msg void OnBnClickedButtonBan();
};
