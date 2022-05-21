
// MFChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFChatClient.h"
#include "MFChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFChatClientDlg 对话框



CMFChatClientDlg::CMFChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORYMSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, &CMFChatClientDlg::OnBnClickedConnectButton)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CMFChatClientDlg::OnBnClickedSendButton)
	ON_BN_CLICKED(IDC_AUTOSEND_RADIO, &CMFChatClientDlg::OnBnClickedAutosendRadio)
	ON_BN_CLICKED(IDC_CLEARMSG_BUTTON, &CMFChatClientDlg::OnBnClickedClearmsgButton)
	ON_BN_CLICKED(IDC_DISCONNECT_BUTTON, &CMFChatClientDlg::OnBnClickedDisconnectButton)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFChatClientDlg 消息处理程序

BOOL CMFChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	// 初始化控件
	GetDlgItem(IDC_SEND_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_RADIO)->EnableWindow(FALSE);
	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));

	m_WordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOR_COMBO, _T("黑色"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// 定义dc
		CPaintDC dc(this);
		// 确认绘制的区域
		CRect rect;
		GetClientRect(&rect);
		TRACE("width = %d, height=%d", rect.Width(), rect.Height());
		// 定义并创建一个内存设备环境，创建兼容性DC
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);
		// 载入资源文件
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmap(IDB_BITMAP_HILL);
		//将图片资源载入到位图里面 bBitMap位图
		BITMAP  bBitMap;
		bmpBackGround.GetBitmap(&bBitMap);
		// 将位图选入临时的内存设备环境
		CBitmap* pBmpOld = dcBmp.SelectObject(&bmpBackGround);
		// 开始绘制
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bBitMap.bmWidth, bBitMap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFChatClientDlg::OnBnClickedConnectButton()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("##OnBnClickedConnectButton");

	GetDlgItem(IDC_SEND_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_RADIO)->EnableWindow(TRUE);

	CString strPort, strIP;
	// 从控件获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	// Cstring 转char *
	USES_CONVERSION;
	LPCSTR  szPort = (LPCSTR)T2A(strPort);
	LPCSTR  szIP= (LPCSTR)T2A(strIP);
	TRACE("szPort = %s, szIP = %s", szPort, szIP);

	int iPort = _ttoi(strPort);
	// 创建socket对象
	m_client = new CMySocket;
	
	// 创建套接字
	if (!m_client->Create())
	{
		TRACE("m_client Create error %d", GetLastError());
		return;
	}

	//连接
	if (m_client->Connect(strIP, iPort) != SOCKET_ERROR)
	{
		TRACE("m_client Connect error %d", GetLastError());
		return;
	}

}

CString CMFChatClientDlg::CatShowString(CString strInfo, CString strMsg) {

	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetTickCount();
	strTime = tmNow.Format("%X  ");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;

	return strShow;
}

void CMFChatClientDlg::OnBnClickedSendButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	// 发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	// 显示到列表框
	CString strShow;
	CString strInfo = _T("我：");
	strShow = CatShowString(strInfo, strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	// 清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
	
}


void CMFChatClientDlg::OnBnClickedAutosendRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(TRUE);
	}
}


void CMFChatClientDlg::OnBnClickedClearmsgButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFChatClientDlg::OnBnClickedDisconnectButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//控制控件
	GetDlgItem(IDC_SEND_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_RADIO)->EnableWindow(FALSE);

	// 回收资源
	m_client->Close();
	if (m_client != NULL)
	{
		delete m_client;
		m_client = NULL;
	} 
	
	// 显示到列表框
	// 显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), _T(" 断开与服务器连接"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


HBRUSH CMFChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);
	if (IDC_HISTORYMSG_LIST == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}

	return hbr;
}


BOOL CMFChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// 规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->message == VK_RETURN)
	{
		return TRUE;
	}
	// 规避空格键
	if (pMsg->message == WM_KEYDOWN && pMsg->message == VK_SPACE)
	{
		return TRUE;
	}

	// 添加快捷键 ctrl + q 退出
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL) < 0) //ctrl 是否被按下
		{
			TRACE("按下Ctrl");
			if (pMsg->wParam == 'q')
			{
				CDialogEx::OnOK();
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
