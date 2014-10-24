#ifndef SERVER_SYSTEM_H_INCLUDED
#define SERVER_SYSTEM_H_INCLUDED

#include <iostream>
#include <memory>
#include <vector>
#include "RakPeerInterface.h"
#include "GetTime.h"

/*
	Handles incoming connections and packets
*/
class ServerSystem {
public:	
	ServerSystem() : port(60000), maxClients(20) {};

	//Initializes the server.
	void startServer(bool userInputDetails);

	//Updates the program time according to RakNet and updates incoming packets.
	void update();

	RakNet::RakPeerInterface* getRakNetInstance();

	//Gets the packets received since the last update
	std::vector<std::shared_ptr<RakNet::BitStream>> getStreams();

	//Returns time since last update, used as clock for whole program
	double getDeltaTime();

private:
	//Pointer to the generated instance of RakPeerInterface
	RakNet::RakPeerInterface *peer;
	//What port the server runs on, only read at init, does not change during runtime
	int port;
	//maximum number of clients, only read at init, does not change during runtime
	int maxClients;
	std::vector<std::shared_ptr<RakNet::BitStream>> receivedStreams;
	//Current time the server is on.
	RakNet::TimeUS currentTime;
	//Previous time.
	RakNet::TimeUS lastTime;

	void receivePackets();
};

#endif