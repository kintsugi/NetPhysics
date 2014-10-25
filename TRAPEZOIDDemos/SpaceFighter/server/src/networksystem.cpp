#include "networksystem.h"
#include "handlemanager.h"
#include "networkcomponent.h"

void NetworkSystem::sendToNetworkComponent(HandleManager &handleManager, std::shared_ptr<RakNet::Packet> packet) {
	//Create a BitStream from the packet.
	std::shared_ptr<RakNet::BitStream> inBS(new RakNet::BitStream(packet->data, packet->length, true));
	//Read the Handle
	inBS->IgnoreBytes(sizeof(RakNet::MessageID));
	Handle networkComponentHandle;
	inBS->Read(networkComponentHandle);
	//Validate the handle and then retrieve the object from the HandleManager.
	NetworkComponent* netComp = (NetworkComponent*)handleManager.get(networkComponentHandle);
	//Add the BitStream to the component.
	netComp->addBitStream(inBS);
}