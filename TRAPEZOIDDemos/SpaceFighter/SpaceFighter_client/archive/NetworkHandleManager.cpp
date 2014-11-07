#include "SpaceFighter_client.h"
#include "NetworkHandleManager.h"

NetworkKey NetworkHandleManager::add(void* dataPtr, const NetworkHandleType type) {
	NetworkKey key = generateKey();
	entries.Add(key, NetworkHandleEntry(type, dataPtr));
	return key;
}

bool NetworkHandleManager::remove(NetworkKey key) {
	//Attempt to find the value with the key
	NetworkHandleEntry* got = entries.Find(key);
	//If found, erase the value and return true
	if (got) {
		entries.Remove(key);
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
