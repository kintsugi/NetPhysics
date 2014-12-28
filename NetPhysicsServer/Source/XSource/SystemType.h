#ifndef SYSTEM_TYPE_H_INCLUDED
#define SYSTEM_TYPE_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef SYSTEM_TYPE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
	enum SystemType {
		//Server Only Systems
#ifdef NET_PHYSICS_SERVER
		SERVER_SYSTEM,
		CLIENT_SYSTEM,
		PHYSICS_SYSTEM,
		PLAYER_INIT_SYSTEM,
		TIMER_SYSTEM,
#endif /* NET_PHYSICS_SERVER */
		//Client Only Systems
#ifdef NET_PHYSICS_CLIENT
		CONNECTION_SYSTEM,
#endif /* NET_PHYSICS_CLIENT */
		//Shared Systems
		PACKET_HANDLER_SYSTEM,
		NETWORK_SYSTEM,
		REPLICATION_SYSTEM,
		NUM_SYSTEM_TYPES,
	};
}

#endif