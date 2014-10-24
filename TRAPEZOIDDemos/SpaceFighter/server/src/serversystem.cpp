#include "serversystem.h"
#include <memory>
#include "BitStream.h"
#include "networkcomponent.h"

void ServerSystem::startServer(bool userInputDetails) {
	if (userInputDetails) {
		std::cout << "Enter server port: ";
		std::cin >> port;
		std::cout << "Enter maximum players or press enter for 20: ";
		std::cin >> maxClients;
	}
	//Get instance of RakNet
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(port, 0);
	//Start server with maximum connections of maxClients
	RakNet::StartupResult r = peer->Startup(maxClients, &sd, 1);
	if (r != RakNet::StartupResult::RAKNET_STARTED)
		std::cout << "Server failed to start. Result code: " << r;
	else {
		peer->SetMaximumIncomingConnections(maxClients);
		std::cout << "Server started successfully.";
	}
	//Start the server clock
	currentTime = RakNet::GetTimeUS();
	lastTime = currentTime;
}

void ServerSystem::update() {
	//TODO calculate server fps
	//Handle incoming packets
	RakNet::Packet *packet;
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
		receivedStreams.push_back(std::shared_ptr<RakNet::BitStream>(new RakNet::BitStream(packet->data, packet->length, true)));
	}
	//Calculate the dt between last server tick
	lastTime = currentTime;
	currentTime = RakNet::GetTimeUS();
}

RakNet::RakPeerInterface* ServerSystem::getRakNetInstance() {
	return peer;
}

std::vector<std::shared_ptr<RakNet::BitStream>> ServerSystem::getStreams() {
	update();
	auto ret = receivedStreams;
	receivedStreams.clear();
	return ret;
}

double ServerSystem::getDeltaTime() {
	return ((double)currentTime - lastTime) / 1000000.0f;
}

void ServerSystem::receivePackets() {

}
