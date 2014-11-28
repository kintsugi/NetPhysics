#ifndef REPLICATION_SYSTEM_H_INCLUDED
#define REPLICATION_SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
#undef REPLICATION_SYSTEM_H_INCLUDED	
#pragma once
#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "System.h"
#include "XLib.h"
#include "RakNetTypes.h"
#include "ReplicationManager.h"

namespace NetPhysics {
	class ReplicationComponent;

	class ReplicationSystem : public System {
	public:

		ReplicationSystem();
		void update(Register &engineRegister);

		void addClient(ReplicationComponent* replicationComponent,
					   RakNet::RakNetGUID clientGUID);
		void removeClient(ReplicationComponent* replicationComponent,
						  RakNet::RakNetGUID clientGUID);
	private:

		XLib::UnorderedMultiMap<ReplicaKey, RakNet::RakNetGUID> masterSlaveList;
	};
}

#endif /* REPLICATION_SYSTEM_H_INCLUDED */