#ifndef NETWORK_MESSAGE_H_INCLUDED
#define NETWORK_MESSAGE_H_INCLUDED

#ifdef CLIENT
	#undef NETWORK_MESSAGE_H_INCLUDED	
	#pragma once
	#include "NetPhysics_client.h"
#endif /* CLIENT */
#ifdef CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* CLIENT */
	#include "RakPeerInterface.h"
	#include "PacketPriority.h"
	#include "MessageIdentifiers.h"
#ifdef CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* CLIENT */
#include "NetworkHandleManager.h"

/*
A message is interpreted based on its type.
All enum members should have a description on the order of the message.
"//<description>
//<RakNet::MessageID>, <param1>, <param2>, ..."
*/

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
	};

	struct Package {

		Package(RakNet::RakPeerInterface* peer,
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

		int send(RakNet::BitStream &bsOut);
	};

	class Send {
	public:

		static int networkComponentMessage(Package &package,
										   RakNet::NetworkID networkID,
										   RakNet::BitStream &bsOut);

		//No client implementation
		static int clientInit(Package &package, NetworkKey networkKey);

		//No server implementation
		static int clientDisconnect(Package &package, NetworkKey networkKey);
	};
}

#endif