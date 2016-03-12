
// LanChatByWCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "stdafx.h"
#include "SessionManager.h"
#include "afxwin.h"
// CLanChatByWCDlg �Ի���
class CLanChatByWCDlg : public CDialogEx
{
// ����
public:
	hash_map<unsigned long ,Session*> sessions;
	SessionManager* sessionManager;
	CLanChatByWCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LANCHATBYWC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLbnSelchangeList7();
	afx_msg void OnBnClickedCancel();
	afx_msg LRESULT HandleMyMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT HandleUserListChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLvnItemDClickList(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit userID;
	CListCtrl UserListControl;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
