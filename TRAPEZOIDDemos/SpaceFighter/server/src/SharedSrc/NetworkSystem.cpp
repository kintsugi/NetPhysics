#include "networksystem.h"
#include "handlemanager.h"
#include "networkcomponent.h"

void NetworkSystem::sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, PacketToBitStream &packet) {
	//Deprecated, needs to be updated


	//Reset the read pointer and ignore the messageID
	packet.bitStream->ResetReadPointer();
	packet.bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::NetworkID networkID;
	packet.bitStream->Read(networkID);
	//Validate the handle and then retrieve the object from the HandleManager.
	NetworkComponent* netComp = networkIDManager.GET_OBJECT_FROM_ID<NetworkComponent*>(networkID);
	//Add the BitStream to the component.
	if (netComp)
		netComp->addBitStream(packet.bitStream);
}