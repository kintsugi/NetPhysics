#include "SpaceFighter_client.h"
#include "ConnectionSystem.h"
#include "BitStream.h"
#include "NetworkMessage.h"

ConnectionSystem::ConnectionSystem(): ipAddress(TEXT("localhost")), port(60000) {}

void ConnectionSystem::update() {
	//Handle incoming packets
	RakNet::Packet *packet;
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
		packetContainer.Add(PacketToBitStream(packet));
	}
}

void ConnectionSystem::connect() {
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd;
	peer->Startup(1, &sd, 1);
	peer->Connect(TCHAR_TO_ANSI(*ipAddress), port, 0, 0);
}

void ConnectionSystem::connect(FString ipAddress, int port) {
	peer->Connect(TCHAR_TO_ANSI(*ipAddress), port, 0, 0);
}

TArray<PacketToBitStream> ConnectionSystem::getPackets() {
	auto ret = packetContainer;
	packetContainer.Reset();
	return ret;
}

RakNet::RakPeerInterface* ConnectionSystem::getRakNetInstance() {
	return peer;
}