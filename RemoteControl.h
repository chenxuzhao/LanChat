#pragma once
#include "afxwin.h"


// RemoteControl �Ի���

class RemoteControl : public CDialogEx
{
	DECLARE_DYNAMIC(RemoteControl)

public:
	ChatDialog* owner;
	RemoteControl(ChatDialog* pParent = NULL);   // ��׼���캯��
	virtual ~RemoteControl();

// �Ի�������
	enum { IDD = IDD_REMOTECONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CEdit m_cmdinptut;
};
