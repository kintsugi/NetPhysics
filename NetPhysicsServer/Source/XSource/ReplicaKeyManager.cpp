#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "ReplicaKeyManager.h"
#include "HandleManager.h"
#include "ReplicationComponent.h"

using namespace NetPhysics;

ReplicaKeyManager::ReplicaKeyManager() : nextAvailableKey(0) {}

#ifdef NET_PHYSICS_SERVER
ReplicaKey ReplicaKeyManager::add(ReplicationComponent* replicationComponent) {
	ReplicaKey key = generateKey();
	entries.insert(std::make_pair(key, replicationComponent->getComponentHandle()));
	return key;
}
#endif /* NET_PHYSICS_SERVER */

bool ReplicaKeyManager::remove(ReplicaKey key) {
	auto got = entries.find(key);
	if (got != entries.end()) {
		entries.erase(got);
		return true;
	}
	return false;
}

ReplicationComponent* ReplicaKeyManager::get(
	ReplicaKey key,
	HandleManager &handleManager)
{
	auto got = entries.find(key);
	if (got != entries.end())
		return reinterpret_cast<ReplicationComponent*>(handleManager.get(got->second));
	return nullptr;
}

void ReplicaKeyManager::set(
	ReplicationComponent* replicationComponent,
	ReplicaKey key)
{
	entries.insert(std::make_pair(key, replicationComponent->getComponentHandle()));
}

ReplicaKey ReplicaKeyManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}