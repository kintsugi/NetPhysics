#ifndef REPLICATION_COMPONENT_H_INCLUDED
#define REPLICATION_COMPONENT_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICATION_COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include <unordered_map>
#include "Register.h"
#include "Component.h"
#include "ComponentList.h"
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicaKeyManager.h"
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
			ReplicaKeyManager &replicationManager);
#endif /* NET_PHYSICS_SERVER */
		ReplicationComponent(
			HandleManager &handleManager,
			ReplicaKeyManager &replicationManager,
			ReplicaKey newKey);

#ifdef NET_PHYSICS_SERVER
		void setReplicationManager(ReplicaKeyManager &replicationManager);
#endif /* NET_PHYSICS_SERVER */
		void setReplicaKey(
			ReplicaKeyManager &replicationManager,
			ReplicaKey newKey);
		ReplicaKey getReplicaKey();
		ComponentList getComponentList();
		std::vector<ComponentType> getTypes();
		void addComponent(ComponentType type);
		void removeComponent(ComponentType type);
		std::unordered_map<ComponentType, bool> getDifferential();
	private:

		ReplicaKey key;
		std::unordered_map<ComponentType, bool> componentDifferential;
		ComponentList componentList;
	};
}

#define NEW_REPLICATION_COMPONENT(rComp) NEW_COMPONENT(NetPhysics::ComponentType::REPLICATION_COMPONENT, rComp)

#endif /* REPLICATION_COMPONENT_H_INCLUDED */