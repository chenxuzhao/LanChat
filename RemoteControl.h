#pragma once
#include "afxwin.h"


// RemoteControl 对话框

class RemoteControl : public CDialogEx
{
	DECLARE_DYNAMIC(RemoteControl)

public:
	ChatDialog* owner;
	RemoteControl(ChatDialog* pParent = NULL);   // 标准构造函数
	virtual ~RemoteControl();

// 对话框数据
	enum { IDD = IDD_REMOTECONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CEdit m_cmdinptut;
};
