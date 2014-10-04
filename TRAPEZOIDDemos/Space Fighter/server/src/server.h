#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "RakPeerInterface.h"
#include "NetworkIDManager.h"
#include "GetTime.h"
#include "messages.h"

/*
	Handles incoming connections
*/
class Server {
protected:
	Server() : port(0), maxClients(0) {};
	//Initializes the server.
	void startServer();
	//Updates the program time according to RakNet and updates incoming packets.
	void updateServer();
	//Gets the packets received since the last update
	std::vector<RakNet::Packet*> getPackets();
	//Returns time since last update, used as clock for whole program
	double getDeltaTime();
	//Pointer to the instance of RakNet for the server to connect to clients.
	RakNet::RakPeerInterface *peer;
private:
	//What port the server runs on, only read at init, does not change during runtime
	int port;
	//maximum number of clients, only read at init, does not change during runtime
	int maxClients;
	std::vector<RakNet::Packet*> currentPackets;
	//Current time the server is on.
	RakNet::TimeUS currentTime;
	//Previous time.
	RakNet::TimeUS lastTime;
};

#endif