#ifndef NETWORK_SYSTEM_H_INCLUDED
#define NETWORK_SYSTEM_H_INCLUDED

#include <memory>
#include "RakNetTypes.h"
#include "NetworkIDManager.h"

//Handles messages to Network Components
class NetworkSystem {
public:
	NetworkSystem() {};
	void sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, std::shared_ptr<RakNet::Packet> packet);
};

#endif