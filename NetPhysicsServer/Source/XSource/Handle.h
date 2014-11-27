#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef HANDLE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
#ifdef NET_PHYSICS_SERVER
	typedef unsigned int uint32;
#endif /*  NET_PHYSICS_SERVER */
	enum HandleType : uint32 {
		UNASSIGNED_HANDLE,
		GAME_OBJECT,
		COMPONENT,
		MESSENGER,
		SUBSCRIBER,
	};

	struct Handle {
		Handle() : key(0), type(UNASSIGNED_HANDLE) {}
		Handle(const uint32 newKey, const HandleType newType) : key(newKey), type(newType) {}

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
}
#endif /* HANDLE_H_INCLUDED */