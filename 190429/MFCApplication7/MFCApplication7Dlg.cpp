
// MFCApplication7Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication7.h"
#include "MFCApplication7Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSliderRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMThemeChangedSliderRed(NMHDR* pNMHDR, LRESULT* pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_RED, &CAboutDlg::OnNMCustomdrawSliderRed)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SLIDER_RED, &CAboutDlg::OnNMThemeChangedSliderRed)
END_MESSAGE_MAP()


// CMFCApplication7Dlg 대화 상자



CMFCApplication7Dlg::CMFCApplication7Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION7_DIALOG, pParent)
	, blueSlider(0)
	, greenSlider(0)
	, redSlider(0)
	, strRed(_T("0"))
	, strGreen(_T("0"))
	, strBlue(_T("0"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLIDER_BLUE, blueCtrl);
	DDX_Control(pDX, IDC_SLIDER_GREEN, greenCtrl);
	DDX_Control(pDX, IDC_SLIDER_RED, redCtrl);
	DDX_Slider(pDX, IDC_SLIDER_BLUE, blueSlider);
	DDV_MinMaxInt(pDX, blueSlider, 0, 255);
	DDX_Slider(pDX, IDC_SLIDER_GREEN, greenSlider);
	DDV_MinMaxInt(pDX, greenSlider, 0, 255);
	DDX_Slider(pDX, IDC_SLIDER_RED, redSlider);
	DDV_MinMaxInt(pDX, redSlider, 0, 255);
	DDX_Control(pDX, IDC_STATIC_VIEW, view);
	DDX_Text(pDX, IDC_EDIT_RED, strRed);
	DDV_MaxChars(pDX, strRed, 3);
	DDX_Text(pDX, IDC_EDIT_GREEN, strGreen);
	DDV_MaxChars(pDX, strGreen, 3);
	DDX_Text(pDX, IDC_EDIT_BLUE, strBlue);
	DDV_MaxChars(pDX, strBlue, 3);
}

BEGIN_MESSAGE_MAP(CMFCApplication7Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMFCApplication7Dlg::OnBnClickedButtonExit)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_RED, &CMFCApplication7Dlg::OnTRBNThumbPosChangingSliderRed)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_GREEN, &CMFCApplication7Dlg::OnTRBNThumbPosChangingSliderGreen)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER_BLUE, &CMFCApplication7Dlg::OnTRBNThumbPosChangingSliderBlue)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_RED, &CMFCApplication7Dlg::OnNMReleasedcaptureSliderRed)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_GREEN, &CMFCApplication7Dlg::OnNMReleasedcaptureSliderGreen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_BLUE, &CMFCApplication7Dlg::OnNMReleasedcaptureSliderBlue)
	ON_EN_CHANGE(IDC_EDIT_RED, &CMFCApplication7Dlg::OnEnChangeEditRed)
	ON_EN_CHANGE(IDC_EDIT_GREEN, &CMFCApplication7Dlg::OnEnChangeEditGreen)
	ON_EN_CHANGE(IDC_EDIT_BLUE, &CMFCApplication7Dlg::OnEnChangeEditBlue)
	//ON_EN_UPDATE(IDC_EDIT_RED, &CMFCApplication7Dlg::OnEnUpdateEditRed)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CMFCApplication7Dlg::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMFCApplication7Dlg::OnBnClickedButtonClear)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCApplication7Dlg 메시지 처리기

BOOL CMFCApplication7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	redCtrl.SetRange(0, 255);
	redCtrl.SetRangeMin(0);
	redCtrl.SetRangeMax(255);
	greenCtrl.SetRange(0, 255);
	greenCtrl.SetRangeMin(0);
	greenCtrl.SetRangeMax(255);
	blueCtrl.SetRange(0, 255);
	blueCtrl.SetRangeMin(0);
	blueCtrl.SetRangeMax(255);

	RECT rt;
	view.GetWindowRect(&rt);
	ScreenToClient(&rt);

	view.SetWindowPos(&wndBottom, rt.left, rt.top, NULL, NULL, SWP_NOREPOSITION | SWP_NOSIZE);

	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication7Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		UpdateData();
		RECT rt;
		view.GetWindowRect(&rt);
		
		ScreenToClient(&rt);
		HBRUSH brush = CreateSolidBrush(RGB(redSlider, greenSlider, blueSlider));
		dc.SelectObject(brush);

		rt.top += rt.bottom + 3;
		rt.bottom += rt.bottom / 2;
		rt.right /= 2;
		//dc.Rectangle(&rt);
		DeleteObject(brush);
		
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnNMCustomdrawSliderRed(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCApplication7Dlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void CAboutDlg::OnNMThemeChangedSliderRed(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 이 기능을 사용하려면 Windows XP 이상이 필요합니다.
	// _WIN32_WINNT 기호는 0x0501보다 크거나 같아야 합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCApplication7Dlg::OnTRBNThumbPosChangingSliderRed(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCApplication7Dlg::OnTRBNThumbPosChangingSliderGreen(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCApplication7Dlg::OnTRBNThumbPosChangingSliderBlue(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
	NMTRBTHUMBPOSCHANGING* pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CMFCApplication7Dlg::OnNMReleasedcaptureSliderRed(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	strRed.Format(_T("%d"), redSlider);
	UpdateData(FALSE);

	Invalidate();
	*pResult = 0;
}


void CMFCApplication7Dlg::OnNMReleasedcaptureSliderGreen(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	strGreen.Format(_T("%d"), greenSlider);
	UpdateData(FALSE);

	Invalidate();
	*pResult = 0;
}


void CMFCApplication7Dlg::OnNMReleasedcaptureSliderBlue(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	strBlue.Format(_T("%d"), blueSlider);
	UpdateData(FALSE);

	Invalidate();
	*pResult = 0;
}


void CMFCApplication7Dlg::OnEnChangeEditRed()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	int red = _ttoi(strRed);
	if (red > 255)
		red = 255;
	strRed.Format(_T("%d"), red);
	redSlider = red;
	UpdateData(FALSE);

	Invalidate();
}


void CMFCApplication7Dlg::OnEnChangeEditGreen()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	int green = _ttoi(strGreen);
	if (green > 255)
		green = 255;
	strGreen.Format(_T("%d"), green);
	greenSlider = green;
	UpdateData(FALSE);
	Invalidate();
}


void CMFCApplication7Dlg::OnEnChangeEditBlue()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	int blue = _ttoi(strBlue);
	if (blue > 255)
		blue = 255;
	strBlue.Format(_T("%d"), blue);
	blueSlider = blue;
	UpdateData(FALSE);
	Invalidate();
}


//void CMFCApplication7Dlg::OnEnUpdateEditRed()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialogEx::OnInitDialog() 함수를 재지정 
//	//하여, IParam 마스크에 OR 연산하여 설정된 ENM_SCROLL 플래그를 지정하여 컨트롤에 EM_SETEVENTMASK 메시지를 보내지 않으면
//	// 편집 컨트롤이 바뀐 텍스트를 표시하려고 함을 나타냅니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	int red = _ttoi(strRed);
//}


void CMFCApplication7Dlg::OnBnClickedButtonApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();

	int red = _ttoi(strRed);
	int green = _ttoi(strGreen);
	int blue = _ttoi(strBlue);

	COLORREF color = RGB(red, green, blue);

	redCtrl.SetPos(red);
	greenCtrl.SetPos(green);
	blueCtrl.SetPos(blue);
	Invalidate();
}


void CMFCApplication7Dlg::OnBnClickedButtonClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//UpdateData();

	//redCtrl.SetPos(0);
	//greenCtrl.SetPos(0);
	//blueCtrl.SetPos(0);

	redSlider = 0;
	greenSlider = 0;
	blueSlider = 0;

	strRed = _T("0");
	strGreen = _T("0");
	strBlue = _T("0");

	UpdateData(FALSE);
	Invalidate();
}


HBRUSH CMFCApplication7Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_VIEW)
	{
		hbr = CreateSolidBrush(RGB(redCtrl.GetPos(), greenCtrl.GetPos(), blueCtrl.GetPos()));
		//hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
