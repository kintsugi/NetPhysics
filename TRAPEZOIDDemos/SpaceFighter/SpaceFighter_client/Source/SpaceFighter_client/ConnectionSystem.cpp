#include "SpaceFighter_client.h"
#include "ConnectionSystem.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"

ConnectionSystem::ConnectionSystem(): ipAddress(TEXT("localhost")), port(60000) {}

void ConnectionSystem::receivePackets() {
	//Handle incoming packets
	RakNet::Packet *packet;
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
		//DeallocatePacket() needs to be called. Copying the packet does not ensure that the
		//data pointer will not be deleted, so the contents of it must be copied.
		TSharedPtr<RakNet::Packet> copy(new RakNet::Packet(*packet));
		copy->data = new unsigned char(*packet->data);
		packetContainer.Add(copy);
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

TArray<TSharedPtr<RakNet::Packet>> ConnectionSystem::getPackets() {
	receivePackets();
	auto ret = packetContainer;
	packetContainer.Reset();
	return ret;
}

RakNet::RakPeerInterface* ConnectionSystem::getRakNetInstance() {
	return peer;
}