#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "ReplicationManager.h"
#include "HandleManager.h"
#include "ReplicationComponent.h"

using namespace NetPhysics;

ReplicationManager::ReplicationManager() : nextAvailableKey(0) {}

#ifdef NET_PHYSICS_SERVER
ReplicaKey ReplicationManager::add(ReplicationComponent* replicationComponent) {
	ReplicaKey key = generateKey();
	entries.insert(std::make_pair(key, replicationComponent->getComponentHandle()));
	return key;
}
#endif /* NET_PHYSICS_SERVER */

bool ReplicationManager::remove(ReplicaKey key) {
	auto got = entries.find(key);
	if (got != entries.end()) {
		entries.erase(got);
		return true;
	}
	return false;
}

ReplicationComponent* ReplicationManager::get(
	ReplicaKey key,
	HandleManager &handleManager)
{
	auto got = entries.find(key);
	if (got != entries.end())
		return reinterpret_cast<ReplicationComponent*>(handleManager.get(got->second));
	return nullptr;
}

void ReplicationManager::set(
	ReplicationComponent* replicationComponent,
	ReplicaKey key)
{
	entries.insert(std::make_pair(key, replicationComponent->getComponentHandle()));
}

ReplicaKey ReplicationManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}