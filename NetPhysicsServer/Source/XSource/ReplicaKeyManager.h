#ifndef REPLICATION_MANAGER_H_INCLUDED
#define REPLICATION_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
#undef REPLICATION_MANAGER_H_INCLUDED	
#pragma once
#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ComponentHandle.h"
#include <unordered_map>

namespace NetPhysics {
	class HandleManager;
	class ReplicationComponent;
	class GameObject;
	typedef uint64_t ReplicaKey;

	class ReplicaKeyManager {
	public:

		ReplicaKeyManager();

#ifdef NET_PHYSICS_SERVER
		ReplicaKey add(ReplicationComponent* replicationComponent);
#endif /* NET_PHYSICS_SERVER */
		bool remove(ReplicaKey key);
		ReplicationComponent* get(
			ReplicaKey key,
			HandleManager &handleManager);
		GameObject* getGameObject(
			ReplicaKey key,
			HandleManager &handleManager);
		void set(
			ReplicationComponent* replicationComponent,
			ReplicaKey key);

	private:

		ReplicaKey nextAvailableKey;
		std::unordered_map<ReplicaKey, ComponentHandle> entries;
		ReplicaKey generateKey();
	};
}

#endif /* REPLICATION_MANAGER_H_INCLUDED */