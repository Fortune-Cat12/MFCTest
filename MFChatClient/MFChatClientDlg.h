
// MFChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"


// CMFChatClientDlg 对话框
class CMFChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnectButton();
	CMySocket* m_client;
	CListBox m_list;
	CEdit m_input;
	afx_msg void OnBnClickedSendButton();
	CString CatShowString(CString strInfo, CString strMsg);
	afx_msg void OnBnClickedAutosendRadio();
};
