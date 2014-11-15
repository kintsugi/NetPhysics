#include "serversystem.h"
#include <memory>
#include "BitStream.h"
#include "networkcomponent.h"
#ifdef SERVER
	#include <iostream>

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

#endif /* SERVER */

void ServerSystem::update() {
	//Handle incoming packets
	RakNet::Packet *packet;
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
		//DeallocatePacket() needs to be called. Copying the packet does not ensure that the
		//data pointer will not be deleted, so the contents of it must be copied.
#ifdef CLIENT
		packetContainer.Add(PacketToBitStream(packet));
#endif CLIENT
#ifdef SERVER
		packetContainer.push_back(PacketToBitStream(packet));
#endif /* SERVER */
	}

#ifdef SERVER
	//Calculate the dt between last server tick
	lastTime = currentTime;
	currentTime = RakNet::GetTimeUS();
#endif /* SERVER */
}

RakNet::RakPeerInterface* ServerSystem::getRakNetInstance() {
	return peer;
}

XLib::Vector<PacketToBitStream> ServerSystem::getPackets() {
	auto ret = packetContainer;
#ifdef SERVER
	packetContainer.clear();
#endif /* SERVER */
#ifdef CLIENT
	packetContainer.Reset();
#endif /* CLIENT */
	return ret;
}

#ifdef SERVER
double ServerSystem::getDeltaTime() {
	return ((double)currentTime - lastTime) / 1000000.0f;
}
#endif /* SERVER */ 