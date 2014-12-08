#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "PacketToBitStream.h"

using namespace NetPhysics;

PacketToBitStream::PacketToBitStream(RakNet::Packet* packet)
	: bitStream(new RakNet::BitStream(packet->data, packet->length, true))
	, guid(packet->guid)
{
	bitStream->Read(messageID);
	bitStream->ResetReadPointer();
}