#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "NetworkSystem.h"
#include "HandleManager.h"
#include "NetworkHandleManager.h"
#include "NetworkComponent.h"
#include "PacketToBitstream.h"

using namespace NetPhysics;

void NetworkSystem::sendToNetworkComponent(NetworkHandleManager &networkHandleManager,
										   PacketToBitStream &packet) {
	//Reset the read pointer and ignore the messageID
	packet.bitStream->ResetReadPointer();
	packet.bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
	NetworkKey networkKey;
	packet.bitStream->Read(networkKey);
	//Validate the handle and then retrieve the object from the HandleManager.
	NetworkComponent* netComp = networkHandleManager.get<NetworkComponent>(networkKey);
	//Add the BitStream to the component.
	if (netComp)
		netComp->addBitStream(packet.bitStream);
}