#include "SpaceFighter_client.h"
#include "NetworkSystem.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "HandleManager.h"
#include "NetworkObject.h"
#include "NetworkComponent.h"

void NetworkSystem::registerActor(HandleManager &handleManager, NetworkObject* networkObject) {
	registeredActors.Add(networkObject->getNetworkID(), networkObject->getHandle());
}

void NetworkSystem::sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, HandleManager &handleManager, PacketToBitStream &packet) {
	//Reset the BitStream read ptr.
	packet.bitStream->ResetReadPointer();
	//Ignore the message, read the NetworkID.
	packet.bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::NetworkID networkID;
	packet.bitStream->Read(networkID);
	//Find the network component and add the bitstream to it. If the network
	NetworkComponent* netComp = networkIDManager.GET_OBJECT_FROM_ID<NetworkComponent*>(networkID);
	if (netComp) {
		netComp->addBitStream(packet.bitStream);
		//Check if the networkID of corresponds to a networkID of a GameNetworkObject
		Handle* got = registeredActors.Find(networkID);
		if (got) {
			NetworkObject* networkObject = (NetworkObject*)handleManager.get(*got);
			if (networkObject)
				networkObject->networkUpdate();
			else
				registeredActors.Remove(networkID);
		}
	}
	
}