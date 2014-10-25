#ifndef NETWORK_SYSTEM_H_INCLUDED
#define NETWORK_SYSTEM_H_INCLUDED

#include <memory>
#include "RakNetTypes.h"

class HandleManager;

//Handles messages to Network Components
class NetworkSystem {
public:
	NetworkSystem() {};
	void sendToNetworkComponent(HandleManager &handleManager, std::shared_ptr<RakNet::Packet> packet );
};

#endif