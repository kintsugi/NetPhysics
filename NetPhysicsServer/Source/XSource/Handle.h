#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef HANDLE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
#ifdef NET_PHYSICS_SERVER
	typedef unsigned long long HandleKey;
#endif /*  NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	typedef uint64_t HandleKey;
#endif /* NET_PHYSICS_CLIENT */
	enum HandleType {
		UNASSIGNED_HANDLE,
		GAME_OBJECT,
		COMPONENT,
		MESSENGER,
		SUBSCRIBER,
	};

	struct Handle {
		Handle() : key(0), type(UNASSIGNED_HANDLE) {}
		Handle(
			const HandleKey newKey,
			const HandleType newType)
			: key(newKey)
			, type(newType) 
		{}

		bool operator==(const Handle& comp) {
			if (comp.key == key && comp.type == type)
				return true;
			else
				return false;
		}
		bool operator!=(const Handle& comp) {
			return !operator==(comp);
		}

		HandleKey key;
		HandleType type;
	};
}
#endif /* HANDLE_H_INCLUDED */