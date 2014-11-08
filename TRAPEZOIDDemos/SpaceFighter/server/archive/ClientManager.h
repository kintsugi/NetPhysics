#ifndef CLIENT_MANAGER_H_INCLUDED
#define CLIENT_MANAGER_H_INCLUDED

#include "xlib.h"
#include "RakPeerInterface.h"
#include "handle.h"
#include "clientcomponent.h"

typedef std::shared_ptr<ClientComponent> ClientComponentPtr;

class HandleManager;

class ClientManager {
public:
	void update(HandleManager &handleManager);
	Handle createComponent(HandleManager &handleManager, RakNet::RakPeerInterface* peer, RakNet::RakNetGUID guid);

private:
	
	XLib::Vector<ClientComponentPtr> container;
};

#endif