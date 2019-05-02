// CinputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication2.h"
#include "CinputDlg.h"
#include "afxdialogex.h"


// CinputDlg 대화 상자

IMPLEMENT_DYNAMIC(CinputDlg, CDialogEx)

CinputDlg::CinputDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUT, pParent)
	, strName(_T(""))
	, strNum(_T(""))
{

}

CinputDlg::~CinputDlg()
{
}

void CinputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, strName);
	DDX_Text(pDX, IDC_EDIT_NUM, strNum);
}


BEGIN_MESSAGE_MAP(CinputDlg, CDialogEx)
END_MESSAGE_MAP()


// CinputDlg 메시지 처리기
