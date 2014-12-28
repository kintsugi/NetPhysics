#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationComponent.h"
#include "HandleManager.h"

using namespace NetPhysics;

ReplicationComponent::ReplicationComponent(
	HandleManager &handleManager)
	: Component(REPLICATION_COMPONENT, handleManager.add(this, COMPONENT)) 
{}

#ifdef NET_PHYSICS_SERVER
ReplicationComponent::ReplicationComponent(
	HandleManager &handleManager, 
	ReplicaKeyManager &replicationManager)
	: Component(REPLICATION_COMPONENT, handleManager.add(this, COMPONENT))
{
	setReplicationManager(replicationManager);
}
#endif /* NET_PHYSICS_SERVER */

ReplicationComponent::ReplicationComponent(
	HandleManager &handleManager,
	ReplicaKeyManager &replicationManager,
	ReplicaKey newKey)
	: Component(REPLICATION_COMPONENT, handleManager.add(this, COMPONENT))
{
	setReplicaKey(replicationManager, newKey);
}

#ifdef NET_PHYSICS_SERVER
void ReplicationComponent::setReplicationManager(
	ReplicaKeyManager &replicationManager) {
	key = replicationManager.add(this);
}
#endif /* NET_PHYSICS_SERVER */

void ReplicationComponent::setReplicaKey(
	ReplicaKeyManager &replicationManager,
	ReplicaKey newKey)
{
	replicationManager.set(this, newKey);
	key = newKey;
}

ReplicaKey ReplicationComponent::getReplicaKey() {
	return key;
}

ComponentList ReplicationComponent::getComponentList() {
	return componentList;
}

std::vector<ComponentType> ReplicationComponent::getTypes(){
	std::vector<ComponentType> ret;
	for (auto iter = componentList.components.begin(); iter != componentList.components.end(); iter++)
		ret.push_back(iter->first);
	return ret;
}

void ReplicationComponent::addComponent(ComponentType type) {
	componentList.add(type);
	componentDifferential.insert(std::make_pair(type, true));
}

void ReplicationComponent::removeComponent(ComponentType type) {
	componentList.remove(type);
	componentDifferential.insert(std::make_pair(type, false));
}

std::unordered_map<ComponentType, bool> ReplicationComponent::getDifferential() {
	std::unordered_map<ComponentType, bool> ret = componentDifferential;
	componentDifferential.clear();
	return ret;
}