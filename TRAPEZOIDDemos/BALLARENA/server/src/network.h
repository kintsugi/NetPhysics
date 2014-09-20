#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include <iostream>
#include <vector>
#include <memory>
#include "RakPeerInterface.h"
#include "messages.h"
#include "networkcomponent.h"


//Deprecated
class Network {
friend class Server;
public:
	~Network() {
		RakNet::RakPeerInterface::DestroyInstance(peer);
	}
	void update();
	NetworkComponent* createNetworkComponent(void(*f)(void *));
	
protected:
	Network():serverPort(60000), maxClients(20) {
		RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
		RakNet::SocketDescriptor sd(serverPort, 0);
		peer->Startup(maxClients, &sd, 1);
		peer->SetMaximumIncomingConnections(maxClients);
		std::cout << "Server started on port: " << serverPort << std::endl;
	}
private:
	const int serverPort;
	const int maxClients;
	RakNet::RakPeerInterface *peer;
	std::vector<NetworkComponent> networkComponents;

};

#endif