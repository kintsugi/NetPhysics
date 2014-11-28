#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationComponent.h"
#include "HandleManager.h"

using namespace NetPhysics;

ReplicationComponent::ReplicationComponent(HandleManager &handleManager) :
										   Component(REPLICATION_COMPONENT,
													 handleManager.add(this,
																	   COMPONENT)) {}

ReplicationComponent::ReplicationComponent(HandleManager &handleManager, 
										   ReplicationManager &replicationManager) : 
										   Component(REPLICATION_COMPONENT,
													 handleManager.add(this,
																	   COMPONENT)) {
	setReplicationManager(replicationManager);
}

ReplicationComponent::ReplicationComponent(HandleManager &handleManager,
										   ReplicationManager &replicationManager,
										   ReplicaKey newKey) :
										   Component(REPLICATION_COMPONENT,
													 handleManager.add(this,
																	   COMPONENT)) {
	setReplicaKey(replicationManager, newKey);
}

void ReplicationComponent::setReplicationManager(ReplicationManager &replicationManager) {
	key = replicationManager.add(this);
}

void ReplicationComponent::setReplicaKey(ReplicationManager &replicationManager, ReplicaKey newKey) {
	replicationManager.set(this, newKey);
	key = newKey;
}

ReplicaKey ReplicationComponent::getReplicaKey() {
	return key;
}

ComponentList ReplicationComponent::getComponentList() {
	return componentList;
}