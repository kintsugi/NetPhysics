#ifndef NETWORK_SYSTEM_H_INCLUDED
#define NETWORK_SYSTEM_H_INCLUDED

#include "RakNetTypes.h"
#include "NetworkIDManager.h"
#include "PacketToBitStream.h"

//Handles messages to Network Components
class NetworkSystem {
public:
	NetworkSystem() {};
	void sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, PacketToBitStream& packet);
};

#endif