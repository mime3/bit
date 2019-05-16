#pragma once


// ConnectDialog 대화 상자

class ConnectDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectDialog)

public:
	ConnectDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ConnectDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONNECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConnect();
	CString IP;
};
