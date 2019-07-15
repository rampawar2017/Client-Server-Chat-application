//Server.cpp

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "ServerComm.h"

using namespace std;

int main(int argc, char* argv[]){
	int		port = 55555, len;
	TCHAR	msg[256];
	ServerComm	server;
	
	// Init Server
	if (!server.Init())
	{
		_tprintf_s(_T("Initialisation Error\n%s"), server.GetErrorText());
		return -1;
	}
	
	// Connect Socket
	if (!server.Connect(_T("127.0.0.1"), port))
	{
		_tprintf_s(_T("Connection Error!"), server.GetErrorText());
		return -1;
	}

	while (1)
	{
		// Wait the Client Message
		msg[0] = 0;
		len = server.Recv(msg, 256);
		if (len > 0)
		{
			_tprintf_s(_T("Received message: %s\n"), msg);
			// send echo message
			server.Send(msg);
			if (_tcsnicmp(msg, _T("quit"), 4) == 0)
				break;
		} else if (len < 0)
		{
			_tprintf_s(_T("Error in receiving message.\n"));
			break;
		}
	}

	return 0;
}
