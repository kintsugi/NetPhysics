#ifndef CLIENT_MANAGER_H_INCLUDED
#define CLIENT_MANAGER_H_INCLUDED

#include <vector>
#include "RakPeerInterface.h"
#include "handle.h"
#include "clientcomponent.h"

class HandleManager;

class ClientManager {
public:
	ClientManager() {}
	void update(HandleManager* handleManager);
	Handle createComponent(HandleManager* handleManager, RakNet::RakNetGUID guid);

private:
	std::vector<ClientComponent> container;
};

#endif