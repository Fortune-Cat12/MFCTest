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
	// �������ݵ�szRecvBuf
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf,200, 0);
	TRACE("###Server OnReceive = %s", szRecvBuf);

	// ��ʾszRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	CString strShow = _T("�ͻ���:  ");
	CString strTime;
	dlg->m_tm = CTime::GetTickCount();
	strTime = dlg->m_tm.Format("%X  ");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	
	CAsyncSocket::OnReceive(nErrorCode);
}