#pragma once

#include "Resource.h"
#include "Session.h"
#include "afxwin.h"

// ChatDialog �Ի���

class ChatDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ChatDialog)
private:
	
	//User
public:
	Session * session;
	BOOL OnInitDialog();
	ChatDialog();
	void sendMsg(Message* msg);
	ChatDialog(CWnd* pParent ,Session* session);   // ��׼���캯��
	virtual ~ChatDialog();

 //�Ի�������
	enum { IDD = IDD_CHATDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT HandleNewMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	
	CEdit m_inptut;
	CListBox allContent;
	afx_msg LRESULT close(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton6();
	CListBox userInfo;
};