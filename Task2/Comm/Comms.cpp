//Comms.cpp

#include "Comms.h"
#include "ServerComm.h"
#include "ClientComm.h"


Comms* CreateConnector(int nType)
{
	Comms* pObj = NULL;
	switch (nType)
	{
	case CT_SERVER:
		#ifdef MY_SERVER_SIDE_APP
		pObj = new ServerComm();
		#endif	//MY_SERVER_SIDE_APP
		break;
	default:
		#ifdef MY_CLIENT_SIDE_APP
		pObj = new ClientComm();
		#endif	//MY_CLIENT_SIDE_APP
		break;
	}
	return pObj;
}
