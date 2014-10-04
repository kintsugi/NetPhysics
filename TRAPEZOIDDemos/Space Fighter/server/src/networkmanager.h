#ifndef NETWORK_MANAGER_H_INCLUDED
#define NETWORK_MANAGER_H_INCLUDED

#include <vector>
#include "handle.h"
#include "networkcomponent.h"

class HandleManager;

class NetworkManager {
public:
	NetworkManager() {}
	void update(HandleManager *handleManager);
	Handle createComponent(HandleManager* handleManager, RakNet::RakPeerInterface* peer, RakNet::NetworkIDManager* manager);
private:
	std::vector<std::unique_ptr<NetworkComponent>> container;
};

#endif