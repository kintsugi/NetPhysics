#ifndef CLIENT_COMPONENT_H_INCLUDED
#define CLIENT_COMPONENT_H_INCLUDED

#include "RakPeerInterface.h"
#include "handlemanager.h"
#include "handle.h"

/*
	PlayerComponent encapsulates data relating the client connected to their game
	entities. Allows for easy access to a client's game state through their
	network component.
*/
class ClientComponent {
public:
	ClientComponent(HandleManager &handleManager, RakNet::RakNetGUID newClientGUID) : 
		clientGUID(newClientGUID),
		handle(handleManager.add(this, CLIENT_COMPONENT)) {}

	RakNet::RakNetGUID getClientGUID() {return clientGUID;}

	Handle getHandle() {return handle;}
private:
	Handle handle;
	RakNet::RakNetGUID clientGUID;
	//TODO design container/system for client state data
};


#endif
