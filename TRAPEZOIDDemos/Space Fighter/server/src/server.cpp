#include "server.h"
#include <memory>
#include "BitStream.h"
#include "networkcomponent.h"

Server::Server(int port) : serverPort(port), maxClients(20) {
	//Get instance of RakNet
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(serverPort, 0);
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

void Server::update() {
	//Calculate the dt between last server tick
	//TODO calculate server fps
	RakNet::Packet *packet;
	lastTime = currentTime;
	currentTime = RakNet::GetTimeUS();
	double dt = ((double)currentTime - lastTime)/1000000.0f;
	//Handle incoming packets
	for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		packetHandler(packet);
	gameWorld.update((float)dt);
}

void Server::packetHandler(RakNet::Packet *packet) {

	switch (packet->data[0]) {
		case ID_NEW_INCOMING_CONNECTION:
			std::cout << std::endl << "A client has connected. System Address: '" << packet->systemAddress.ToString() << "'";
		case ID_DISCONNECTION_NOTIFICATION:
			break;
		case NETWORK_COMPONENT_MESSAGE:	
			updateNetworkComponent(packet);
			break;
	}
}

//WARNING: C# client and server interactions untested
void Server::updateNetworkComponent(RakNet::Packet *packet) {
	RakNet::NetworkID networkComponentNetworkID;
	//get the guid of the client
	RakNet::RakNetGUID componentGUID = packet->guid;
	//Create the bitstream
	RakNet::BitStream in(packet->data, packet->length, false);
	//Skip the messageID
	in.IgnoreBytes(sizeof(RakNet::MessageID));
	//Read the networkComponent ID
	//TODO test this since client sends it as a C# ulong not as a NetworkObjectID
	in.Read(networkComponentNetworkID);
	//Find the corresponding NetworkComponent and update the in bitstream
	NetworkComponent* netcomp = networkIDManager.GET_OBJECT_FROM_ID<NetworkComponent*>(networkComponentNetworkID);
	if (netcomp->getGUID().operator==(componentGUID)) {
		std::unique_ptr<RakNet::BitStream> newIn(new RakNet::BitStream(packet->data, packet->length, true));
		netcomp->in = std::move(newIn);
	}
}