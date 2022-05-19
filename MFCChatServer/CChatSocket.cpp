#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"
#include "MFCChatServer.h"

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
	char szRecvBuf[SEND_SERVER_BUF] = { 0 };
	Receive(szRecvBuf, SEND_SERVER_BUF, 0);
	TRACE("###Server OnReceive = %s", szRecvBuf);

	// 显示szRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow;
	CString strInfo = _T("客户端:");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);
	
	CAsyncSocket::OnReceive(nErrorCode);
}