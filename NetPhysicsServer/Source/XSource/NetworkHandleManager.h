#ifndef NETWORK_HANDLE_MANAGER_H_INCLUDED
#define NETWORK_HANDLE_MANAGER_H_INCLUDED

#ifdef CLIENT
	#undef NETWORK_HANDLE_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */
#include "XLib.h"
#include "NetworkHandleObject.h"

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

template<class T>
T* NetworkHandleManager::get(NetworkKey key) {
	//Attempt to find the value with the key handle.id
#ifdef SERVER
	auto got = entries.find(key);

	if(got != entries.end())
		return (T*)got->second.entry;
#endif /* SERVER */
#ifdef CLIENT
	NetworkHandleEntry* got = entries.Find(key);
	if (got)
		return (T*)got;
#endif CLIENT
	return false;
}

#endif