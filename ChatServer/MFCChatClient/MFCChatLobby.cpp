// MFCChatLobby.cpp: 구현 파일
//

#include "pch.h"
#include "MFCChatClient.h"
#include "MFCChatLobby.h"
#include "afxdialogex.h"


// MFCChatLobby 대화 상자

IMPLEMENT_DYNAMIC(MFCChatLobby, CDialogEx)

MFCChatLobby::MFCChatLobby(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOBBY, pParent)
	, roomName(_T(""))
{

}

MFCChatLobby::~MFCChatLobby()
{
}

void MFCChatLobby::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ROOMLIST, roomList);
	DDX_Text(pDX, IDC_EDIT_ROOMNAME, roomName);
	DDV_MaxChars(pDX, roomName, 15);
}


BEGIN_MESSAGE_MAP(MFCChatLobby, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &MFCChatLobby::OnBnClickedButtonCreate)
	ON_LBN_DBLCLK(IDC_LIST_ROOMLIST, &MFCChatLobby::OnLbnDblclkListRoomlist)
END_MESSAGE_MAP()


// MFCChatLobby 메시지 처리기


void MFCChatLobby::OnBnClickedButtonCreate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void MFCChatLobby::OnLbnDblclkListRoomlist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
