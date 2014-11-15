#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "NetworkHandleManager.h"

NetworkKey NetworkHandleManager::add(void* dataPtr, const NetworkHandleType type) {
	NetworkKey key = generateKey();
#ifdef SERVER
	entries.insert(std::make_pair(key, NetworkHandleEntry(type, dataPtr)));
#endif /* SERVER */
#ifdef CLIENT
	entries.Add(key,NetworkHandleEntry(type, dataPtr)));
#endif /* CLIENT */
	return key;
}

bool NetworkHandleManager::remove(NetworkKey key) {
#ifdef SERVER
	//Attempt to find the value with the key
	auto got = entries.find(key);
	//If found, erase the value and return true
	if(got != entries.end()) {
		entries.erase(got);
		return true;
	}
#endif /* SERVER */
#ifdef CLIENT
	NetworkHandleEntry* got = entries.Find(key);
	if (got) {
		entries.Remove(key);
		return true;
	}
#endif /* CLIENT */
	return false;
}

NetworkKey NetworkHandleManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}
