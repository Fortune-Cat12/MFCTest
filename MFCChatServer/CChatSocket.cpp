#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"

CChatSocket::CChatSocket()
{

}

CChatSocket::~CChatSocket() 
{

}
void CChatSocket::OnReceive(int nErrorCode) {
	TRACE("###Server OnReceive");
	// 接收数据到szRecvBuf
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf,200, 0);
	TRACE("###Server OnReceive = %s", szRecvBuf);

	// 显示szRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow = _T("客户端:  ");
	CString strTime;
	dlg->m_tm = CTime::GetTickCount();
	strTime = dlg->m_tm.Format("%X  ");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	
	CAsyncSocket::OnReceive(nErrorCode);
}