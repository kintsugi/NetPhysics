#ifndef REPLICATION_COMPONENT_H_INCLUDED
#define REPLICATION_COMPONENT_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICATION_COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include <unordered_map>
#include "Component.h"
#include "ComponentList.h"
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationManager.h"
#include "RakNetTypes.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
	class ReplicationComponent : public Component {
	public:
		/*
		 * Describes which components the client side G.O. should contain.
		 */
		ReplicationComponent(HandleManager &handleManager);
#ifdef NET_PHYSICS_SERVER
		ReplicationComponent(
			HandleManager &handleManager,
			ReplicationManager &replicationManager);
#endif /* NET_PHYSICS_SERVER */
		ReplicationComponent(
			HandleManager &handleManager,
			ReplicationManager &replicationManager,
			ReplicaKey newKey);

#ifdef NET_PHYSICS_SERVER
		void setReplicationManager(ReplicationManager &replicationManager);
#endif /* NET_PHYSICS_SERVER */
		void setReplicaKey(
			ReplicationManager &replicationManager,
			ReplicaKey newKey);
		ReplicaKey getReplicaKey();
		std::vector<ComponentType> getComponents();
		void addComponent(ComponentType type);
		void removeComponent(ComponentType type);
		std::unordered_map<ComponentType, bool> getDifferential();
	private:

		ReplicaKey key;
		std::unordered_map<ComponentType, bool> componentDifferential;
		ComponentList componentList;
	};
}


#endif /* REPLICATION_COMPONENT_H_INCLUDED */