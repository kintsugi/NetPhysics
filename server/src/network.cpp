#include "network.h"

Network::Network() : serverPort(60000), maxClients(20) {
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor sd(serverPort, 0);
	peer->Startup(maxClients, &sd, 1);
	peer->SetMaximumIncomingConnections(maxClients);
	std::cout << "Server started on port: " << serverPort << std::endl;
	
}

void Network::update() {

}

