#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServerDlg.h"
#include "MFCChatServer.h"

CServerSocket::CServerSocket()
{

}
CServerSocket::~CServerSocket()
{

}

void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("###OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	// 接收连接
	Accept(*(dlg->m_chat));

	CString strShow;
	CString strInfo = _T("客户端连接成功");
	CString strMsg = _T("");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}