#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <iostream>
#include <vector>
#include "RakPeerInterface.h"
#include "NetworkIDManager.h"
#include "GetTime.h"
#include "messages.h"
#include "world.h"
#include "ball.h"

/*
	Main system class of the program. Updates and controls all other systems.
*/
class Server {
public:
	Server(int);
	//Updates all other systems
	void update();
private:
	//What port the server runs on
	const int serverPort;
	//maximum number of clients
	const int maxClients;
	//Pointer to the instance of RakNet for the server to connect to clients.
	RakNet::RakPeerInterface *peer;
	//Current time the server is on.
	RakNet::TimeUS currentTime;
	//Previous time.
	RakNet::TimeUS lastTime;
	//NetworkIDManager for calling references to the objects that inherit NetworkIDObject
	RakNet::NetworkIDManager networkIDManager;
	//Physics simulator
	World gameWorld;
	//Data for connected players. TODO write an entity handler
	std::vector<Ball> players;
	/*
		Reads the first byte of a packet (which should correspond to an enum in Message.h
		@param packet pointer to packet to handle
	*/
	void packetHandler(RakNet::Packet *packet);
	//@param guid guid of the client that controls the ball.
	void createBallEntity(RakNet::RakNetGUID);
	/*
		Updates the inbound data of networkComponent determined by the networkID field.
		Note that from clients the networkID is a C# ulong but on the server its a uint64_t
		@param packet pointer of the packet container the network component bitstream
	*/

	void deleteBallEntity(RakNet::RakNetGUID);
	void updateNetworkComponent(RakNet::Packet *packet);
	
	
};

#endif