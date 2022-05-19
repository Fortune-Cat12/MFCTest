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

//�ص�����д����������
void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("###OnConnect");
	CMFChatClientDlg* dlg = (CMFChatClientDlg*) AfxGetApp()->GetMainWnd();
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("����������ӳɹ�");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode) 
{
	TRACE("###Client OnReceive ");
	// �������ݵ�szRecvBuf
	CMFChatClientDlg* dlg = (CMFChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);
	TRACE("###Client OnReceive = %s", szRecvBuf);

	// ��ʾszRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);

	CString strShow;
	CString strInfo = _T("����ˣ�");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	dlg->UpdateData(FALSE);

	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) 
	{
		// ��ȡ�༭������
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);

		//��������ʽ��ʱ��+�ǳ�+[�Զ��ظ�]+����
		CString strMsg = _T("[�Զ��ظ�]") + strAutoSendMsg;
		char* szsendBuf = T2A(strMsg);

		dlg->m_client->Send(szsendBuf, SEND_MAX_BUF, 0);

		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}

	CAsyncSocket::OnReceive(nErrorCode);
}

