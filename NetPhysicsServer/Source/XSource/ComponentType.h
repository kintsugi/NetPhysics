#ifndef COMPONENT_TYPE_H_INCLUDED
#define COMPONENT_TYPE_H_INCLUDED

#ifdef CLIENT
	#undef COMPONENT_TYPE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

enum ComponentType {
#ifdef SERVER
	CLIENT,
	PHYSICS,
	PLAYER_STATE,
	TIMER,
	SCRIPT,
#endif /* SERVER */
	NETWORK,
	NUM_COMPONENT_TYPES
};

#endif /* COMPONENT_TYPE_H_INCLUDED */