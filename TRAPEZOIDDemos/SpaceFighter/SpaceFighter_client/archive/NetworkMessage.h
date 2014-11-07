#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "RakPeerInterface.h"
#include "PacketPriority.h"
#include "MessageIdentifiers.h"
#include "HideWindowsPlatformTypes.h"

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



		//No server implementation
		static int clientDisconnect(Package &package, RakNet::NetworkID networkID);
	};
}