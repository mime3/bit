// CTextDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCApplication4.h"
#include "CTextDlg.h"
#include "afxdialogex.h"


// CTextDlg 대화 상자

IMPLEMENT_DYNAMIC(CTextDlg, CDialogEx)

CTextDlg::CTextDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEXT, pParent)
	, strTextInput(_T(""))
{

}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT_INPUT, strTextInput);
	DDV_MaxChars(pDX, strTextInput, 30);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialogEx)
END_MESSAGE_MAP()


// CTextDlg 메시지 처리기
