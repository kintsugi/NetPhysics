#pragma once

#include "SpaceFighter_client.h"
#include "networkhandleobject.h"
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

	TMap<NetworkKey, NetworkHandleEntry> entries;
};

template<class T>
T* NetworkHandleManager::get(NetworkKey key) {
	//Attempt to find the value with the key handle.id
	NetworkHandleEntry* got = entries.Find(key);

	if (got) {
		return (T*)got->entry;
	}
	return false;
}
