#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "NetworkHandleManager.h"

using namespace NetPhysics;

NetworkKey NetworkHandleManager::add(void* dataPtr,
									 const NetworkHandleType type) {
	NetworkKey key = generateKey();
	entries.insert(key, NetworkHandleEntry(type, dataPtr));
	return key;
}

bool NetworkHandleManager::remove(NetworkKey key) {
	NetworkHandleEntry* got = entries.find(key);
	if (got) {
		entries.erase(key);
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
