#include "networksystem.h"
#include "handlemanager.h"
#include "networkcomponent.h"

void NetworkSystem::sendToNetworkComponent(RakNet::NetworkIDManager &networkIDManager, std::shared_ptr<RakNet::Packet> packet) {
	//Create a BitStream from the packet.
	std::shared_ptr<RakNet::BitStream> inBS(new RakNet::BitStream(packet->data, packet->length, true));
	//Read the Handle
	inBS->IgnoreBytes(sizeof(RakNet::MessageID));
	RakNet::NetworkID networkID;
	inBS->Read(networkID);
	//Validate the handle and then retrieve the object from the HandleManager.
	NetworkComponent* netComp = networkIDManager.GET_OBJECT_FROM_ID<NetworkComponent*>(networkID);
	//Add the BitStream to the component.
	if (netComp)
		netComp->addBitStream(inBS);
}