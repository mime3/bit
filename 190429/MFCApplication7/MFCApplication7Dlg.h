
// MFCApplication7Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication7Dlg 대화 상자
class CMFCApplication7Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication7Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION7_DIALOG };
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
	CSliderCtrl blueCtrl;
	CSliderCtrl greenCtrl;
	CSliderCtrl redCtrl;
//	CString strRed;
//	CString strGreen;
//	CString strBlue;
	CStatic view;
	afx_msg void OnBnClickedButtonExit();
	int blueSlider;
	int greenSlider;
	int redSlider;
	afx_msg void OnTRBNThumbPosChangingSliderRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTRBNThumbPosChangingSliderGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTRBNThumbPosChangingSliderBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureSliderRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureSliderGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMReleasedcaptureSliderBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditRed();
	afx_msg void OnEnChangeEditGreen();
	afx_msg void OnEnChangeEditBlue();
//	afx_msg void OnEnUpdateEditRed();
	CString strRed;
	CString strGreen;
	CString strBlue;
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonClear();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
