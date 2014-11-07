#include "SpaceFighter_client.h"
#include "NetworkSystem.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "NetworkHandleManager.h"
#include "HandleManager.h"
#include "NetworkObject.h"
#include "NetworkComponent.h"

void NetworkSystem::registerActor(HandleManager &handleManager, NetworkObject* networkObject) {
	registeredActors.Add(networkObject->getNetworkKey(), networkObject->getHandle());
}

void NetworkSystem::sendToNetworkComponent(NetworkHandleManager &networkHandleManager, HandleManager &handleManager, PacketToBitStream &packet) {
	//Reset the BitStream read ptr.
	packet.bitStream->ResetReadPointer();
	//Ignore the message, read the NetworkID.
	packet.bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
	NetworkKey networkKey;
	packet.bitStream->Read(networkKey);
	//Find the network component and add the bitstream to it. If the network
	NetworkComponent* netComp = networkHandleManager.get<NetworkComponent>(networkKey);
	if (netComp) {
		netComp->addBitStream(packet.bitStream);
		//Check if the networkID of corresponds to a networkID of a GameNetworkObject
		Handle* got = registeredActors.Find(networkKey);
		if (got) {
			NetworkObject* networkObject = (NetworkObject*)handleManager.get(*got);
			if (networkObject)
				networkObject->networkUpdate();
			else
				registeredActors.Remove(networkKey);
		}
	}
	
}