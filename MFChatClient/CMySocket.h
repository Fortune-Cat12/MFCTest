#pragma once
#include <afxsock.h>

class CMySocket :
    public CAsyncSocket
{
public:
    CMySocket();
    virtual ~CMySocket();
    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
};

