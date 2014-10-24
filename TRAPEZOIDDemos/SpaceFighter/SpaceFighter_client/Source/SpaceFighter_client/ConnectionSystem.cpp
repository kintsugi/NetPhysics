#include "SpaceFighter_client.h"
#include "ConnectionSystem.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"

ConnectionSystem::ConnectionSystem(): ipAddress(TEXT("localhost")), port(60000) {}

void ConnectionSystem::receivePackets() {
	//Handle incoming packets
	RakNet::Packet *packet;
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		receivedStreams.Add(TSharedPtr<RakNet::BitStream>(new RakNet::BitStream(packet->data, packet->length, true)));
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

TArray<TSharedPtr<RakNet::BitStream>> ConnectionSystem::getStreams() {
	receivePackets();
	auto ret = receivedStreams;
	receivedStreams.Reset();
	return ret;
}

RakNet::RakPeerInterface* ConnectionSystem::getRakNetInstance() {
	return peer;
}