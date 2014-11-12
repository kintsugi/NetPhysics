#ifdef CLIENT
	#include "NetPhysics_client.h"
#endif /* CLIENT */
#include "NetworkMessage.h"
#ifdef CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* CLIENT */
	#include "BitStream.h"
#ifdef CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* CLIENT */

NetworkMessage::Package::Package(RakNet::RakPeerInterface* peer,
										RakNet::AddressOrGUID to /* = RakNet::AddressOrGUID() */,
										PacketPriority priority /* = HIGH_PRIORITY */,
										PacketReliability reliability /* = RELIABLE_ORDERED */,
										char orderingChannel /* = 0 */,
										bool broadcast /* = false */,
										uint32_t forceReceiptNumber /* = 0 */) :
	peer(peer),
	to(to),
	priority(priority),
	reliability(reliability),
	orderingChannel(orderingChannel),
	broadcast(broadcast),
	forceReceiptNumber(forceReceiptNumber) {}

int NetworkMessage::Package::send(RakNet::BitStream &bsOut) {
	return peer->Send(&bsOut, priority, reliability, orderingChannel, to, broadcast, forceReceiptNumber);
}

int NetworkMessage::Send::networkComponentMessage(Package &package,
										   RakNet::NetworkID networkID,
										   RakNet::BitStream &bsOut) 
{
	//Construct a BitStream following order: MessageID, NetworkID, <data>
	RakNet::BitStream bsForm;
	bsForm.Write((RakNet::MessageID)(NETWORK_COMPONENT_MESSAGE));
	bsForm.Write(networkID);
	bsForm.Write(bsOut);
	//Send
	return package.send(bsForm);
}

int NetworkMessage::Send::clientInit(Package &package, NetworkKey networkKey) {
	//Construct a BitStream following order: MessageID, NetworkID
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)(CLIENT_INIT));
	bsOut.Write(networkKey);
	bsOut.Write(bsOut);
	//Send
	return package.send(bsOut);
}