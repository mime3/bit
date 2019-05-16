// ConnectDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCChatClient.h"
#include "ConnectDialog.h"
#include "afxdialogex.h"


// ConnectDialog 대화 상자

IMPLEMENT_DYNAMIC(ConnectDialog, CDialogEx)

ConnectDialog::ConnectDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONNECT, pParent)
	, IP(_T("127.0.0.1"))
{

}

ConnectDialog::~ConnectDialog()
{
}

void ConnectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP, IP);
}


BEGIN_MESSAGE_MAP(ConnectDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ConnectDialog::OnBnClickedButtonConnect)
END_MESSAGE_MAP()


// ConnectDialog 메시지 처리기


void ConnectDialog::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//this->DestroyWindow();
	EndDialog(IDOK);
}
