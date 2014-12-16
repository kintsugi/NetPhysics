#ifndef REPLICATION_SYSTEM_H_INCLUDED
#define REPLICATION_SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICATION_SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "System.h"
#include "XLib.h"
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationManager.h"
#include "RakNetTypes.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ComponentList.h"

namespace NetPhysics {
	class GameObject;
	class ReplicationComponent;

	class ReplicationSystem : public System {
	public:

		ReplicationSystem();
		void update(Register &reg);

#ifdef NET_PHYSICS_SERVER
		void addClient(ReplicationComponent* replicationComponent,
			RakNet::RakNetGUID clientGUID);
		void removeClient(ReplicationComponent* replicationComponent,
			RakNet::RakNetGUID clientGUID);

		//TODO returns array of guids that use that key
		void getClient(ReplicaKey);

	private:

		void processSends(Register &reg);
		void send(
			Register &reg,
			GameObject* gameObject,
			ReplicationComponent* replicationComponent);

		XLib::UnorderedMultiMap<ReplicaKey, RakNet::RakNetGUID> masterSlaveList;
#endif /* NET_PHYSICS_SERVER */
		ComponentList componentList;
	};
}

#endif /* REPLICATION_SYSTEM_H_INCLUDED */