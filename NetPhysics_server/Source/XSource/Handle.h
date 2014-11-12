#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#ifdef CLIENT
	#undef HANDLE_H_INCLUDED	
	#pragma once
	#include "NetPhysics_client.h"
#endif /* CLIENT */

typedef unsigned int uint32;

enum HandleType : uint32 {
	//Universal handle types.
	UNASSIGNED_HANDLE_TYPE,
	MESSENGER_HANDLE,
	SUBSCRIBER_HANDLE,
	//Server only handle types.
	GAME_OBJECT,
	NETWORK_COMPONENT_HANDLE,
	PHYSICS_COMPONENT_HANDLE,
	CLIENT_COMPONENT_HANDLE,
	PLAYER_STATE_COMPONENT_HANDLE,
	TIMER_COMPONENT_HANDLE,
	//Client only types.
	NETWORK_OBJECT_HANDLE,
};

struct Handle
{
	Handle() : key(0), type(UNASSIGNED_HANDLE_TYPE), ifActive(false) {}

	Handle(uint32 newID, HandleType newType) : key(newID), type(newType), ifActive(true) {}

	bool operator==(const Handle& comp) {
		if (comp.key == key && comp.type == type)
			return true;
		else
			return false;
	}

	bool operator!=(const Handle& comp) {
		return !operator==(comp);
	}

	uint32 key;
	HandleType type;
	bool ifActive;
};

#endif /* HANDLE_H_INCLUDED */