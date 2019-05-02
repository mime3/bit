#pragma once


// CinputDlg 대화 상자

class CinputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CinputDlg)

public:
	CinputDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CinputDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTICLASS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 이름
	CString strName;
	// 학번
	CString strNum;
};
