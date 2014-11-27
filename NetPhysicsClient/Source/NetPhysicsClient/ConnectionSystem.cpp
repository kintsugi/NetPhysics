#include "NetPhysicsClient.h"
#include "ConnectionSystem.h"
#include "AllowWindowsPlatformTypes.h"
	#include "RakPeerInterface.h"
#include "HideWindowsPlatformTypes.h"

using namespace NetPhysics;

ConnectionSystem::~ConnectionSystem() {
	RakNet::SystemAddress* remoteSystem = 0;
	uint32* numberOfSystems = 0;
	rakPeerInstance->GetConnectionList(remoteSystem, (unsigned short*)numberOfSystems);
	for (uint32 i = 0; i < *numberOfSystems; i++) {
		rakPeerInstance->CloseConnection(*(remoteSystem + i), true);
	}
}

void ConnectionSystem::init() {
	rakPeerInstance = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd;
	rakPeerInstance->Startup(1, &sd, 1);
}

RakNet::RakPeerInterface* ConnectionSystem::getRakPeerInstance() {
	return rakPeerInstance;
}

XLib::Vector<PacketToBitStream> ConnectionSystem::getPackets() {
	RakNet::Packet *packet;
	XLib::Vector<PacketToBitStream> packetContainer;
	for (packet = rakPeerInstance->Receive(); packet; rakPeerInstance->DeallocatePacket(packet), packet = rakPeerInstance->Receive())
		packetContainer.Add(PacketToBitStream(packet));
	return packetContainer;
}