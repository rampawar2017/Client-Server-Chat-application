//Client.cpp

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "ClientComm.h"

using namespace std;


int _tmain(int argc, _TCHAR* argv[]) {
	int		port = 55555, len;
	TCHAR	msg[DEFAULT_SEND_BUFLEN];
	ClientComm	client;
	
	// Init Socket
	if (!client.Init())
	{
		_tprintf_s(_T("Initialisation Error\n%s"), client.GetErrorText());
		return -1;
	}
	
	// Connect Server
	if (!client.Connect(_T("127.0.0.1"), port))
	{
		_tprintf_s(_T("Connection Error!"), client.GetErrorText());
		return -2;
	}

	_tprintf_s(_T("Connection success! Please enter your message.\nOtherwise, type QUIT to exit client and server applciations.\n"));
	while (1)
	{
		// Wait user input
		_getts_s(msg, DEFAULT_SEND_BUFLEN);
		
		// Send String to server
		client.Send(msg);

		// Receive echo
		len = client.Recv(msg, DEFAULT_SEND_BUFLEN);
		if (len > 0)
			_tprintf(_T("Received echo message: %s\n"), msg);
		
		if (_tcsnicmp(msg, _T("quit"), 4) == 0)
			break;
	}

	return 0;
}

