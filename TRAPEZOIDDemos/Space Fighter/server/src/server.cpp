#include "server.h"
#include <memory>
#include "BitStream.h"
#include "networkcomponent.h"

void Server::startServer(){
	std::cout << "Enter server port: ";
	std::cin >> port;
	std::cout << "Enter maximum players or press enter for 20: ";
	std::cin >> maxClients;
	//Get instance of RakNet
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(port, 0);
	//Start server with maximum connections of maxClients
	RakNet::StartupResult r = peer->Startup(maxClients, &sd, 1);
	if (r != RakNet::StartupResult::RAKNET_STARTED)
		std::cout << std::endl << "Server failed to start. Result code: " << r;
	else {
		std::cout << std::endl << "Server started successfully.";
		peer->SetMaximumIncomingConnections(maxClients);
	}
	//Start the server clock
	currentTime = RakNet::GetTimeUS();
	lastTime = currentTime;
}

void Server::updateServer() {
	//Calculate the dt between last server tick
	//TODO calculate server fps
	RakNet::Packet *packet;
	lastTime = currentTime;
	currentTime = RakNet::GetTimeUS();
	
	//Handle incoming packets
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		currentPackets.push_back(packet);
}

std::vector<RakNet::Packet*> Server::getPackets() {
	std::vector<RakNet::Packet*> ret = currentPackets;
	currentPackets.clear();
	return ret;
}

double Server::getDeltaTime() {
	return ((double)currentTime - lastTime) / 1000000.0f;
}
