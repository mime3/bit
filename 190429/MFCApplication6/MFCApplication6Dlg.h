
// MFCApplication6Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication6Dlg 대화 상자
class CMFCApplication6Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication6Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	void Init();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 학번
	CString strNum;
	// 이름
	CString strName;
	CString strCell;
	// 주관식
	BOOL chA;
	// 객관식
	BOOL chB;
	// 온라인등록
	CButton online;
	// 방문등록
	CButton offline;
	// 주관식 문항 수
	CComboBox cbPoint1;
	// 객관식 문항 수
	CComboBox cbPoint2;
	// 리스트컨트롤
	CListCtrl listView;
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonExit();
};
