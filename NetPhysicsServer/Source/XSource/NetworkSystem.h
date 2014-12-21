#ifndef NETWORK_SYSTEM_H_INCLUDED
#define NETWORK_SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef NETWORK_MESSAGE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "System.h"

namespace NetPhysics {
	class NetworkHandleManager;
	struct PacketToBitStream;

	//Handles messages to Network Components
	class NetworkSystem : public System {
	public:
		NetworkSystem() {};
		void sendToNetworkComponent(NetworkHandleManager &networkHandleManager,
			PacketToBitStream& packet);
	};
}

#endif