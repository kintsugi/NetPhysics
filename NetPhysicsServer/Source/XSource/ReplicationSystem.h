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
#include "StreamFormatter.h"
#include <set>

namespace NetPhysics {
	class GameObject;
	class ReplicationComponent;

	class ReplicationSystem : public System {
	public:

		enum ReplicationMessageType {
			CREATE_GAME_OBJECT,
			DESTROY_GAME_OBJECT,
			COMPONENT_MESSAGE,
			CREATE_COMPONENT,
			DESTROY_COMPONENT,
		};

		ReplicationSystem();
		void update(Register &reg);
		//Processes incoming Replication messages.
		void receive(Register &reg, RakNet::BitStream &bsIn);
#ifdef NET_PHYSICS_SERVER
		bool ReplicationSystem::addSlave(
			Register &reg,
			GameObject *gameObject,
			RakNet::RakNetGUID clientGUID);
		bool removeSlave(
			Register &reg, 
			GameObject *gameObject,
			RakNet::RakNetGUID clientGUID);
		std::vector<RakNet::RakNetGUID> getSlaves(ReplicaKey key);

	private:

		void applyDifferential(
			Register &reg,
			GameObject* gameObject,
			ReplicationComponent *replicationComponent);
		void applyComponentReplication(
			Register &reg,
			GameObject *gameObject,
			ReplicationComponent *replicationComponent);

		std::unordered_multimap<ReplicaKey, RakNet::RakNetGUID> masterSlaveList;
#endif /* NET_PHYSICS_SERVER */

		struct ReplicationMessage {
			ReplicationMessage(ReplicationMessageType type, ReplicaKey key);
			ReplicationMessageType type;
			ReplicaKey key;
			ComponentType compType;
			RakNet::BitStream *bsOut;
		};

		void componentMessageResponse(Register &reg, ReplicationMessage &msg);
#ifdef NET_PHYSICS_CLIENT
		void createGameObjectResponse(Register &reg, ReplicationMessage &msg);
		void destroyGameObjectResponse(Register &reg, ReplicationMessage &msg);
		void createComponentResponse(Register &reg, ReplicationMessage &msg);
		void destroyComponentResponse(Register &reg, ReplicationMessage &msg);
#endif /* NET_PHYSICS_CLIENT */


		class ReplicationStreamFormatter : public StreamFormatter<ReplicationMessage> {
		public:
			ReplicationMessage* format(RakNet::BitStream &bsIn);
		};

		ComponentList componentList;
	};
}

#endif /* REPLICATION_SYSTEM_H_INCLUDED */