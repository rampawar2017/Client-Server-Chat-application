//ServerComm.h

#pragma once
//pre processor directives
#ifdef	MY_SERVER_SIDE_APP

#include "Comms.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_RECV_BUFLEN	512

class ServerComm : public Comms
{
public:
	ServerComm(void);
	~ServerComm(void);

	bool Init();
	void Close();
	int	 GetErrorCode();
	TCHAR* GetErrorText();

	bool Connect(TCHAR* lpszAddr, int port);
	void Disconnect();

	int	 Send(TCHAR* lpszText);
	int	 Recv(TCHAR* lpszText, int nMaxLen);

private:
	SOCKET	serverSocket;		//Server Socket
	SOCKET	clientSocket;		//Client Socket

	TCHAR	szErrorMsg[DEFAULT_RECV_BUFLEN];	//Error Text
	int		lastError;			//Error Code

	void Error2Text(TCHAR* prefix, int nError);
};

#endif	//MY_SERVER_SIDE_APP