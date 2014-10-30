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

void NetworkSystem::sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, HandleManager &handleManager, TSharedPtr<RakNet::Packet> packet) {
	//Create a BitStream from the packet.
	TSharedPtr<RakNet::BitStream> inBS(new RakNet::BitStream(packet->data, packet->length, true));
	//Ignore the message, read the NetworkID
	inBS->IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::NetworkID networkID;
	inBS->Read(networkID);
	//Find the network component and add the bitstream to it. If the network
	NetworkComponent* netComp = networkIDManager.GET_OBJECT_FROM_ID<NetworkComponent*>(networkID);
	if (netComp) {
		netComp->addBitStream(inBS);
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