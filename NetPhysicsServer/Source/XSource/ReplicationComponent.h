#ifndef REPLICATION_COMPONENT_H_INCLUDED
#define REPLICATION_COMPONENT_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICATION_COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Component.h"
#include "ComponentList.h"
#include "XLib.h"
#include "RakNetTypes.h"
#include "ReplicationManager.h"

namespace NetPhysics {
	class ReplicationComponent : public Component {
	public:

		ReplicationComponent(HandleManager &handleManager);
		ReplicationComponent(HandleManager &handleManager, 
							 ReplicationManager &replicationManager);
		ReplicationComponent(HandleManager &handleManager,
							 ReplicationManager &replicationManager,
							 ReplicaKey newKey);

		void setReplicationManager(ReplicationManager &replicationManager);
		void setReplicaKey(ReplicationManager &replicationManager,
						   ReplicaKey newKey);
		ReplicaKey getReplicaKey();
		ComponentList getComponentList();

	private:

		ReplicaKey key;
		ComponentList componentList;
	};
}


#endif /* REPLICATION_COMPONENT_H_INCLUDED */