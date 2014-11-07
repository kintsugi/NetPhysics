#ifndef NETWORK_HANDLE_MANAGER_H_INCLUDED
#define NETWORK_HANDLE_MANAGER_H_INCLUDED

#include "xlib.h"
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
	auto got = entries.find(key);

	if(got != entries.end()) {
		return (T*)got->second.entry;
	}
	return false;
}

#endif