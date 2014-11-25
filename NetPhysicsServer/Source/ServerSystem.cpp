#include "serversystem.h"
#include <memory>
#include "BitStream.h"
#include "networkcomponent.h"
#include <iostream>

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
		std::cout << "Server failed to start. Result code: " << r;
	else {
		rakPeerInstance->SetMaximumIncomingConnections(maxClients);
		std::cout << "Server started successfully.";
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

XLib::Vector<PacketToBitStream> ServerSystem::getPackets() {
	auto ret = packetContainer;
	packetContainer.clear();
	return ret;
}