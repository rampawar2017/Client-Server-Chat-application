//Comms.h
#pragma once

#include <tchar.h>

//abstract class
class Comms
{
public:
	virtual bool Init() = 0;
	virtual void Close() = 0;
	virtual int	 GetErrorCode() = 0;
	virtual TCHAR* GetErrorText() = 0;

	//Connect
	virtual bool Connect(TCHAR* lpszAddr, int nPort) = 0;
	//Disconnect
	virtual void Disconnect() = 0;	

	//send message
	virtual int  Send(TCHAR* lpszText) = 0;
	//receive message
	virtual int  Recv(TCHAR* lpszText, int nMaxLen) = 0;
};

//Connector Type Constants
#define		CT_SERVER	0
#define		CT_CLIENT	1

extern Comms* CreateConnector(int nType);//create pointer to external function, nType is kind of communication module

