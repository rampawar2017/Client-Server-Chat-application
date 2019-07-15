//ClientComm.h
#pragma once
//pre processor diretive
#ifdef	MY_CLIENT_SIDE_APP

#include "Comms.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#define		DEFAULT_SEND_BUFLEN		512

class ClientComm : public Comms
{
public:
	ClientComm(void);
	~ClientComm(void);

	bool Init();
	void Close();
	int	 GetErrorCode();
	TCHAR* GetErrorText();

	bool Connect(TCHAR* lpszAddr, int port);
	void Disconnect();

	int	 Send(TCHAR* lpszText);
	int	 Recv(TCHAR* lpszText, int nMaxLen);

private:
	SOCKET	clientSocket;		//Client Socket

	TCHAR	szErrorMsg[DEFAULT_SEND_BUFLEN];	//Error Text
	int		lastError;			//Error Code

	void	Error2Text(TCHAR* prefix, int nError);
};

#endif	//MY_CLIENT_SIDE_APP