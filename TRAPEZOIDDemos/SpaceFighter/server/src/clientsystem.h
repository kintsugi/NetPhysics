#ifndef CLIENT_SYSTEM_H_INCLUDED
#define CLIENT_SYSTEM_H_INCLUDED

#include "RakNetTypes.h"
#include "gameobjectfilter.h"

class ManagerRegister;

class ClientSystem {
public:
	ClientSystem();
	/*
	Creates a GameObject with a client component containing
	the client's, effectively adding him to the system.
	@param clientSystemAddress the clients systemAddress.
	*/
	void initializeClient(ManagerRegister &managerRegister,
						  RakNet::RakPeerInterface* peer,
						  RakNet::RakNetGUID guid);
private:
	GameObjectFilter filter;
};


#endif