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

	CString str;
	dlg->m_tm = CTime::GetTickCount();
	str = dlg->m_tm.Format("%X  ");
	str += _T("与客户端连接成功");
	dlg->m_list.AddString(str);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}