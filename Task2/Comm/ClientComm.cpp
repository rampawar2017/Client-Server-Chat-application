//ClientComm.cpp

#include "Comms.h"
#include "ClientComm.h"
#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

ClientComm::ClientComm(void)
{
	clientSocket = INVALID_SOCKET;
}


ClientComm::~ClientComm(void)
{
	Close();
}

bool ClientComm::Init()
{
	int wsaerr;
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	lastError = wsaerr;
	if (wsaerr != 0) {
		_stprintf_s(szErrorMsg, 256, _T("The Winsock dll not found! Status : %d"), wsaerr);
		return false;
	}
	else
		_stprintf_s(szErrorMsg, 256, _T("The Winsock dll foundd! Status : %d"), wsaerr);

	return true;
}
void ClientComm::Close()
{
	Disconnect();
	WSACleanup();
}
int	 ClientComm::GetErrorCode()
{
	return lastError;
}
TCHAR*	 ClientComm::GetErrorText()
{
	return szErrorMsg;
}

bool ClientComm::Connect(TCHAR* lpszAddr, int port)
{
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		Error2Text(_T("Error in socket()"), WSAGetLastError());
		return false;
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, lpszAddr, &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR){
		Error2Text(_T("Error in Connecting to Server"), WSAGetLastError());
		return false;
	}

	return true;
}
void ClientComm::Disconnect()
{
	if (clientSocket != INVALID_SOCKET)
	{
		shutdown(clientSocket, SD_BOTH);
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
	}
}

int	 ClientComm::Send(TCHAR* msg)
{
	int len = (_tcslen(msg) + 1) * sizeof(TCHAR);
	len = send(clientSocket, (const char*) msg, len, 0);
	return len;
}

int  ClientComm::Recv(TCHAR* msg, int nMaxLen)
{
	return recv(clientSocket, (char*) msg, DEFAULT_SEND_BUFLEN * sizeof(TCHAR), 0);
}


//Define all possible errors while using WSA, full list can be found on microsoft website
void ClientComm::Error2Text(TCHAR* prefix, int nError)
{
	int	len = 0;
	if ((prefix != NULL) && (prefix[0] != 0))
		len = _stprintf_s(szErrorMsg, DEFAULT_SEND_BUFLEN, _T("%s: "), prefix);

	switch (nError)
	{
	case WSANOTINITIALISED:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("A successful WSAStartup call must occur before using this function."));
		break;
	case WSAENETDOWN:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The network subsystem has failed."));
		break;
	case WSAEACCES:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST socket option to enable use of the broadcast address."));
		break;
	case WSAEINTR:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall."));
		break;
	case WSAEINPROGRESS:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."));
		break;
	case WSAEFAULT:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The buf parameter is not completely contained in a valid part of the user address space."));
		break;
	case WSAENETRESET:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress."));
		break;
	case WSAENOBUFS:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("No buffer space is available."));
		break;
	case WSAENOTCONN:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The socket is not connected."));
		break;
	case WSAENOTSOCK:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The descriptor is not a socket."));
		break;
	case WSAEOPNOTSUPP:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("MSG_OOB was specified, but the socket is not stream-style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations."));
		break;
	case WSAESHUTDOWN:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH."));
		break;
	case WSAEWOULDBLOCK:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The socket is marked as nonblocking and the requested operation would block."));
		break;
	case WSAEMSGSIZE:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The socket is message oriented, and the message is larger than the maximum supported by the underlying transport."));
		break;
	case WSAEHOSTUNREACH:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The remote host cannot be reached from this host at this time."));
		break;
	case WSAEINVAL:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled."));
		break;
	case WSAECONNABORTED:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable."));
		break;
	case WSAECONNRESET:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The virtual circuit was reset by the remote side executing a hard or abortive close. For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a \"Port Unreachable\" ICMP packet. The application should close the socket as it is no longer usable."));
		break;
	case WSAETIMEDOUT:
		_stprintf_s(szErrorMsg + len, DEFAULT_SEND_BUFLEN - len, _T("The connection has been dropped, because of a network failure or because the system on the other end went down without notice."));
		break;
	}
}
