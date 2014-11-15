#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#ifdef CLIENT
	#undef HANDLE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

typedef unsigned int uint32;

enum HandleType : uint32 {
	UNASSIGNED_HANDLE,
#ifdef SERVER
	GAME_OBJECT,
#endif /* SERVER */
#ifdef CLIENT

#endif /* CLIENT */
	COMPONENT,
	MESSENGER,
	SUBSCRIBER,
};

struct Handle
{
	Handle() : key(0), type(UNASSIGNED_HANDLE) {}

	Handle(uint32 newKey, HandleType newType) : key(newKey), type(newType){}

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
};

#endif /* HANDLE_H_INCLUDED */