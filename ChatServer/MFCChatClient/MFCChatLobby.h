#pragma once


// MFCChatLobby 대화 상자

class MFCChatLobby : public CDialogEx
{
	DECLARE_DYNAMIC(MFCChatLobby)

public:
	MFCChatLobby(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MFCChatLobby();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOBBY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox roomList;
	CString roomName;
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnLbnDblclkListRoomlist();
};
