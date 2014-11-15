#ifndef SERVER_SYSTEM_H_INCLUDED
#define SERVER_SYSTEM_H_INCLUDED

#include <iostream>
#include "System.h"
#include "XLib.h"
#include "RakPeerInterface.h"
#include "GetTime.h"
#include "packettobitstream.h"

/*
	Handles incoming connections and packets
*/
class ServerSystem : public System {
public:

#ifdef SERVER
	ServerSystem() : port(60000), maxClients(20) {};
	//Initializes the server.
	void startServer(bool userInputDetails);
#endif /* CLIENT */
#ifdef CLIENT
	ServerSystem() : hostIP("localhost"), port(60000) {}
	void connect();
	void connect(RakNet::RakString hostIP, uint32 hostPort);
#endif /* CLIENT */

	//Updates the program time according to RakNet on the server and updates incoming packets.
	void update();

	RakNet::RakPeerInterface* getRakNetInstance();

	//Gets the packets received since the last update
	XLib::Vector<PacketToBitStream> getPackets();

#ifdef SERVER
	//Returns time since last update, used as clock for whole program
	double getDeltaTime();
#endif /* SERVER */

private:

	//Pointer to the generated instance of RakPeerInterface
	RakNet::RakPeerInterface *peer;
	//What port the server runs on, only read at init, does not change during runtime
	int port;

	XLib::Vector<PacketToBitStream> packetContainer;
#ifdef SERVER
	//maximum number of clients, only read at init, does not change during runtime
	int maxClients;
	//Current time the server is on.
	RakNet::TimeUS currentTime;
	//Previous time.
	RakNet::TimeUS lastTime;
#endif /* SERVER */
#ifdef CLIENT
	uint32 hostPost;
	RakNet::RakString hostIP;
#endif /* CLIENT */
};

#endif /* SERVER_SYSTEM_H_INCLUDED */