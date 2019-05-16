// ChatDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ChatClient.h"
#include "ChatDlg.h"
#include "afxdialogex.h"

WCHAR g_IP[20];
WCHAR g_nickName[20];
std::map<INT64, User*> g_userMap;

// ChatDlg 대화 상자

IMPLEMENT_DYNAMIC(ChatDlg, CDialogEx)

ChatDlg::ChatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ChatDlg::~ChatDlg()
{
	client->Stop();
}

void ChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAT, ChatList);
	DDX_Control(pDX, IDC_LIST_USER, UserList);
	DDX_Control(pDX, IDC_EDIT_CHAT, Edit_Chat);
	DDX_Control(pDX, IDC_STATIC_ID, Static_ID);
	DDX_Control(pDX, IDC_STATIC_NICK, Static_Nick);
	DDX_Control(pDX, IDC_STATIC_CON, Static_Con);
}


BEGIN_MESSAGE_MAP(ChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &ChatDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// ChatDlg 메시지 처리기


void ChatDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (client->_connected == false)
		return;

	if (Edit_Chat.GetWindowTextLengthW() == 0)
		return;

	Packet* req_Chat = PacketAlloc(LanClient);
	client->MakePacket_Req_Chat(req_Chat);
	client->SendPacket(req_Chat);
	PacketFree(req_Chat);

	Edit_Chat.SetWindowTextW(L"");
}


BOOL ChatDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	client = new ChatLanClient(this);
	client->Start();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
