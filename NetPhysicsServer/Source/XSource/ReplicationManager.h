#ifndef REPLICATION_MANAGER_H_INCLUDED
#define REPLICATION_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
#undef REPLICATION_MANAGER_H_INCLUDED	
#pragma once
#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
#include "ComponentHandle.h"

namespace NetPhysics {
	class HandleManager;
	class ReplicationComponent;
	typedef unsigned int ReplicaKey;

	class ReplicationManager {
	public:

		ReplicationManager();

#ifdef NET_PHYSICS_SERVER
		ReplicaKey add(ReplicationComponent* replicationComponent);
#endif /* NET_PHYSICS_SERVER */
		bool remove(ReplicaKey key);
		ReplicationComponent* get(ReplicaKey key,
								  HandleManager &handleManager);
		void set(ReplicationComponent* replicationComponent,
				 ReplicaKey key);

	private:

		ReplicaKey nextAvailableKey;
		XLib::UnorderedMap<ReplicaKey, ComponentHandle> entries;
		ReplicaKey generateKey();
	};
}

#endif /* REPLICATION_MANAGER_H_INCLUDED */