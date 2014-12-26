#ifndef NETWORK_MESSAGE_H_INCLUDED
#define NETWORK_MESSAGE_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef NETWORK_MESSAGE_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
	//For RakNet::AddressOrGUID
	#include "RakNetTypes.h"
	#include "PacketPriority.h"
	#include "MessageIdentifiers.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "NetworkHandleManager.h"
#include "ReplicationManager.h"

namespace RakNet {
	class RakPeerInterface;
}

/*
A message is interpreted based on its type.
All enum members should have a description on the order of the message.
"//<description>
//<RakNet::MessageID>, <param1>, <param2>, ..."
*/
namespace NetPhysics {
	namespace NetworkMessage {
		enum ID {
			//Denotes a message for a network component.
			//RakNet::MessageID, RakNet::NetworkID
			NETWORK_COMPONENT_MESSAGE = ID_USER_PACKET_ENUM + 1,
			//Sent from server to clients when they are properly configured.
			//RakNet::MessageID, RakNet::NetworkID
			CLIENT_INIT,
			//Sent from client to server when then client willfully disconnects.
			//RakNet::MessageID, RakNet::NetworkID
			CLIENT_DISCONNECT,
			//Sent from server to a client to consruct a component for a G.O.
			//RakNet::MessageID, ReplicaKey, ComponentType, <Constructor Params>...
			REPLICATION_CREATE_COMPONENT,
			//Sent from server to a client to destroy a component of a G.O.
			//RakNet::MessageID, ReplicaKey, ComponentType
			REPLICATION_DESROY_COMPONENT

		};

		struct Package {

			Package(
				RakNet::RakPeerInterface* peer,
				RakNet::AddressOrGUID to = RakNet::AddressOrGUID(),
				PacketPriority priority = HIGH_PRIORITY,
				PacketReliability reliability = RELIABLE_ORDERED,
				char orderingChannel = 0,
				bool broadcast = false,
				uint32_t forceReceiptNumber = 0);

			RakNet::RakPeerInterface* peer;
			PacketPriority priority;
			PacketReliability reliability;
			char orderingChannel;
			RakNet::AddressOrGUID to;
			bool broadcast;
			uint32_t forceReceiptNumber;
			uint32_t send(RakNet::BitStream &bsOut);
		};

		namespace Send {
			uint32_t networkComponentMessage(
				Package &package,
				RakNet::NetworkID networkID,
				RakNet::BitStream &bsOut);
			uint32_t clientInit(
				Package &package,
				NetworkKey networkKey);
			uint32_t clientDisconnect(
				Package &package,
				NetworkKey networkKey);
			uint32_t createComponent(
				Package &package, 
				ReplicaKey key, 
				ComponentType type, 
				RakNet::BitStream &constructorParams);
			uint32_t destroyComponent(
				Package &package,
				ReplicaKey key,
				ComponentType type);
		};
	}
}

#endif