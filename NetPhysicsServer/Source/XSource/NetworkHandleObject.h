#ifndef NETWORK_HANDLE_OBJECT_H_INCLUDED
#define NETWORK_HANDLE_OBJECT_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef NETWORK_HANDLE_OBJECT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
	typedef unsigned long long NetworkKey;
	class NetworkHandleManager;

	enum NetworkHandleType {
		UNDEFINED_TYPE,
	};

	class NetworkHandleObject {
	public:

		NetworkHandleObject(void *newSuper) : super(newSuper), type(UNDEFINED_TYPE), key(0) {}
		NetworkHandleObject(void *super, NetworkHandleType newType) : type(UNDEFINED_TYPE), key(0) {}
		~NetworkHandleObject();

		NetworkKey getNetworkKey();
		NetworkHandleType getType();
		void setNetworkHandleManager(NetworkHandleManager &networkHandleManager);
		bool operator==(const NetworkHandleObject& comp);
		bool operator!=(const NetworkHandleObject& comp);

	private:

		NetworkHandleManager* owningManager;
		void* super;
		NetworkHandleType type;
		NetworkKey key;
	};
}

#endif