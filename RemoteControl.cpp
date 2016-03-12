// RemoteControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LanChatByWC.h"
#include "RemoteControl.h"
#include "afxdialogex.h"


// RemoteControl �Ի���

IMPLEMENT_DYNAMIC(RemoteControl, CDialogEx)

RemoteControl::RemoteControl(ChatDialog* pParent /*=NULL*/)
: CDialogEx(RemoteControl::IDD, pParent), owner(pParent)
{

}

RemoteControl::~RemoteControl()
{
}

void RemoteControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_cmdinptut);
}


BEGIN_MESSAGE_MAP(RemoteControl, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &RemoteControl::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &RemoteControl::OnBnClickedOk)
END_MESSAGE_MAP()


// RemoteControl ��Ϣ�������


void RemoteControl::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void RemoteControl::OnBnClickedOk()
{
	CString str;

	m_cmdinptut.GetWindowText(str);
	char buf[256];

	sprintf_s(buf, "%S", str);

	std::string strin = (CStringA)str;
	Message msg;
	msg.FromID = owner->session->m_my_ID;
	msg.ToID = owner->session->m_user.ID;
	CTime time = CTime::GetCurrentTime();
	msg.time = CTime::GetCurrentTime();
	msg.msg_type = msg_type_cmd;


	msg.content = strin;
	owner->sendMsg(&msg);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
