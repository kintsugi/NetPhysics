#ifndef COMPONENT_TYPE_H_INCLUDED
#define COMPONENT_TYPE_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef COMPONENT_TYPE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */



namespace NetPhysics {
	enum ComponentType {
		NULL_COMPONENT,
#ifdef NET_PHYSICS_SERVER
		//Components defined for server only.
		CLIENT_COMPONENT,
		PHYSICS_COMPONENT,
		PLAYER_STATE_COMPONENT,
		TIMER_COMPONENT,
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		//Components defined for client only.
#endif /* NET_PHYSICS_CLIENT */
		//Components defined on both systems.
		NETWORK_COMPONENT,
		REPLICATION_COMPONENT,
		SCRIPT_COMPONENT,
		NUM_COMPONENT_TYPES,
	};
}

#endif /* COMPONENT_TYPE_H_INCLUDED */