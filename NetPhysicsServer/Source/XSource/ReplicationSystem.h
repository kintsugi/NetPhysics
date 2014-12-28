#ifndef REPLICATION_SYSTEM_H_INCLUDED
#define REPLICATION_SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICATION_SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "System.h"
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicaKeyManager.h"
#include "RakNetTypes.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ComponentList.h"
#include "NetworkMessage.h"
#include <set>

namespace NetPhysics {
	class GameObject;
	class ReplicationComponent;

	class ReplicationSystem : public System {
	public:

		ReplicationSystem();
		void update(Register &reg);

#ifdef NET_PHYSICS_SERVER
		bool ReplicationSystem::addSlave(
			Register &reg,
			GameObject* gameObject,
			RakNet::RakNetGUID clientGUID);
		bool removeSlave(
			Register &reg, 
			GameObject* gameObject,
			RakNet::RakNetGUID clientGUID);
		std::vector<RakNet::RakNetGUID> getSlaves(ReplicaKey key);

	private:

		void applyDifferential(
			Register &reg,
			GameObject* gameObject,
			ReplicationComponent* replicationComponent);
		void applyComponentReplication(
			Register &reg,
			GameObject* gameObject,
			ReplicationComponent* replicationComponent);

		std::unordered_multimap<ReplicaKey, RakNet::RakNetGUID> masterSlaveList;
#endif /* NET_PHYSICS_SERVER */
		ComponentList componentList;
	};

	namespace NetworkMessage {
		namespace Send {
			uint32_t createGameObject(
				Package &package,
				ReplicaKey key);
			uint32_t destroyGameObject(
				Package &package,
				ReplicaKey key);
			uint32_t createComponent(
				Package &package,
				ReplicaKey key,
				ComponentType type,
				RakNet::BitStream &constructorParams);
			uint32_t destroyComponent(
				Package &package,
				ReplicaKey key,
				ComponentType type);
			uint32_t messageComponent(
				Package &package,
				ReplicaKey key,
				ComponentType type,
				RakNet::BitStream &bsOut);
		}
	}
}

#endif /* REPLICATION_SYSTEM_H_INCLUDED */