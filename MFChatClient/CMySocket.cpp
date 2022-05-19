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
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("与服务器连接成功");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode) 
{
	TRACE("###Client OnReceive ");
	// 接收数据到szRecvBuf
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("###Client OnReceive = %s", szRecvBuf);

	// 显示szRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);

	CString strShow;
	CString strInfo = _T("服务端：");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) 
	{
		// 获取编辑框内容
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);

		//封包，组格式：时间+昵称+[自动回复]+内容
		CString strMsg = _T("[自动回复]") + strAutoSendMsg;
		char* szsendBuf = T2A(strMsg);

		dlg->m_client->Send(szsendBuf, SEND_MAX_BUF, 0);

		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

