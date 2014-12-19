#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "NetworkHandleManager.h"

using namespace NetPhysics;

NetworkKey NetworkHandleManager::add(void* dataPtr,
									 const NetworkHandleType type) {
	NetworkKey key = generateKey();
#ifdef NET_PHYSICS_SERVER
	entries.insert(key, NetworkHandleEntry(type, dataPtr));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	entries.Add(key,NetworkHandleEntry(type, dataPtr));
#endif /* NET_PHYSICS_CLIENT */
	return key;
}

bool NetworkHandleManager::remove(NetworkKey key) {
#ifdef NET_PHYSICS_SERVER
	//Attempt to find the value with the key
	auto got = entries.find(key);
	//If found, erase the value and return true
	if(got != entries.end()) {
		entries.erase(got);
		return true;
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	NetworkHandleEntry* got = entries.Find(key);
	if (got) {
		entries.Remove(key);
		return true;
	}
#endif /* NET_PHYSICS_CLIENT */
	return false;
}

NetworkKey NetworkHandleManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}
