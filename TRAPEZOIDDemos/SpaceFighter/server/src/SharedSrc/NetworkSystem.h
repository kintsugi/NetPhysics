#ifndef NETWORK_SYSTEM_H_INCLUDED
#define NETWORK_SYSTEM_H_INCLUDED

#include "System.h"

struct PacketToBitStream;
class NetworkHandleManager;

//Handles messages to Network Components
class NetworkSystem : public System {
public:
	NetworkSystem() {};
	void sendToNetworkComponent(NetworkHandleManager &networkHandleManager, PacketToBitStream& packet);
};

#endif