#include "pch.h"
#include "CMySocket.h"
#include "MFChatClientDlg.h"
#include "MFChatClient.h"

CMySocket::CMySocket() 
{

}

CMySocket:: ~CMySocket() 
{

}

//回调，重写：满足需求
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("###OnConnect");
	CMFChatClientDlg* dlg = (CMFChatClientDlg*) AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X  ");
	str += _T("与服务器连接成功");
	dlg->m_list.AddString(str);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode) 
{
	TRACE("###Client OnReceive ");
	// 接收数据到szRecvBuf
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);
	TRACE("###Client OnReceive = %s", szRecvBuf);

	// 显示szRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow = _T("服务端:  ");
	CString strTime;
	dlg->m_tm = CTime::GetTickCount();
	strTime = dlg->m_tm.Format("%X  ");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	CAsyncSocket::OnReceive(nErrorCode);
}

