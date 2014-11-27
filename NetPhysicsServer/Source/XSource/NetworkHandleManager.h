#ifndef NETWORK_HANDLE_MANAGER_H_INCLUDED
#define NETWORK_HANDLE_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef NETWORK_HANDLE_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
#include "NetworkHandleObject.h"

namespace NetPhysics {
	class NetworkHandleManager {
	public:

		NetworkHandleManager() : nextAvailableKey(0) {}

		NetworkKey add(void* dataPtr, const NetworkHandleType type);
		template<class T>
		T* get(NetworkKey key);
		bool remove(NetworkKey key);

	private:

		NetworkKey nextAvailableKey;
		struct NetworkHandleEntry {
			NetworkHandleEntry(const NetworkHandleType newType, void* dataPtr) : type(newType), entry(dataPtr) {}
			NetworkHandleType type;
			void* entry;
		};
		NetworkKey generateKey();
		XLib::UnorderedMap<NetworkKey, NetworkHandleEntry> entries;
	};
}

template<class T>
T* NetPhysics::NetworkHandleManager::get(NetworkKey key) {
	//Attempt to find the value with the key handle.id
#ifdef NET_PHYSICS_SERVER
	auto got = entries.find(key);

	if(got != entries.end())
		return (T*)got->second.entry;
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	NetworkHandleEntry* got = entries.Find(key);
	if (got)
		return (T*)got;
#endif NET_PHYSICS_CLIENT
	return false;
}

#endif