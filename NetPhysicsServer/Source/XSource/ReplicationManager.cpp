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
#ifdef NET_PHYSICS_SERVER
	entries.insert(std::make_pair(key, replicationComponent->getComponentHandle()));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	entries.Add(key, replicationComponent->getComponentHandle());
#endif /* NET_PHYSICS_CLIENT */
	return key;
}
#endif /* NET_PHYSICS_SERVER */

bool ReplicationManager::remove(ReplicaKey key) {
#ifdef NET_PHYSICS_SERVER
	auto got = entries.find(key);
	if (got != entries.end()) {
		entries.erase(got);
		return true;
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	ComponentHandle* got = entries.Find(key);
	if (got) {
		entries.Remove(key);
		return true;
	}
#endif /* NET_PHYSICS_CLIENT */
	return false;
}

ReplicationComponent* ReplicationManager::get(
	ReplicaKey key,
	HandleManager &handleManager)
{
#ifdef NET_PHYSICS_SERVER
	auto got = entries.find(key);
	if (got != entries.end()) {
		return reinterpret_cast<ReplicationComponent*>(handleManager.get(got->second));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	ComponentHandle* got = entries.Find(key);
	if (got) {
		return reinterpret_cast<ReplicationComponent*>(handleManager.get(*got));
#endif /* NET_PHYSICS_CLIENT */
	}
	return nullptr;
}

void ReplicationManager::set(
	ReplicationComponent* replicationComponent,
	ReplicaKey key)
{
#ifdef NET_PHYSICS_SERVER
	entries.insert(std::make_pair(key, replicationComponent->getComponentHandle()));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	entries.Add(key, replicationComponent->getComponentHandle());
#endif /* NET_PHYSICS_CLIENT */
}

ReplicaKey ReplicationManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}