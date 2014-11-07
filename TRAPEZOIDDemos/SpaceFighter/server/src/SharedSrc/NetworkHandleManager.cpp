#include "networkhandlemanager.h"

NetworkKey NetworkHandleManager::add(void* dataPtr, const NetworkHandleType type) {
	NetworkKey key = generateKey();
	entries.insert(std::make_pair(key, NetworkHandleEntry(type, dataPtr)));
	return key;
}

bool NetworkHandleManager::remove(NetworkKey key) {
	//Attempt to find the value with the key
	auto got = entries.find(key);
	//If found, erase the value and return true
	if(got != entries.end()) {
		entries.erase(got);
		return true;
	}
	return false;
}

NetworkKey NetworkHandleManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}
