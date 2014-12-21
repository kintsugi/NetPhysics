#include "serversystem.h"
#include "BitStream.h"
#include "Logger.h"

using namespace NetPhysics;

void ServerSystem::init() {
	//Get instance of RakNet
	rakPeerInstance = RakNet::RakPeerInterface::GetInstance();
	port = DEFAULT_PORT;
	maxClients = DEFAULT_MAX_CLIENTS;
}

void ServerSystem::startServer(bool userInputDetails) {
	if (userInputDetails) {
		std::cout << "Enter server port: ";
		std::cin >> port;
		std::cout << "Enter maximum players or press enter for 20: ";
		std::cin >> maxClients;
	}
	//Start server with maximum connections of maxClients
	RakNet::SocketDescriptor sd(port, 0);
	RakNet::StartupResult r = rakPeerInstance->Startup(maxClients, &sd, 1);
	if (r != RakNet::StartupResult::RAKNET_STARTED)
		LOG(ERROR_MSG, "Server failed to start. Result code: " + r);
	else {
		rakPeerInstance->SetMaximumIncomingConnections(maxClients);
		LOG(LOG_MSG, "Server started successfully.");
	}
}

void ServerSystem::update() {
	//Handle incoming packets
	RakNet::Packet *packet;
	for (packet = rakPeerInstance->Receive(); packet; rakPeerInstance->DeallocatePacket(packet), packet = rakPeerInstance->Receive())
		packetContainer.push_back(PacketToBitStream(packet));
}

RakNet::RakPeerInterface* ServerSystem::getRakPeerInstance() {
	return rakPeerInstance;
}

std::vector<PacketToBitStream> ServerSystem::getPackets() {
	auto ret = packetContainer;
	packetContainer.clear();
	return ret;
}