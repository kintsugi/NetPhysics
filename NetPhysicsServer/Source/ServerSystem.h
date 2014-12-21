#ifndef SERVER_SYSTEM_H_INCLUDED
#define SERVER_SYSTEM_H_INCLUDED

#include <vector>
#include <iostream>
#include "System.h"
#include "RakPeerInterface.h"
#include "GetTime.h"
#include "packettobitstream.h"

#define DEFAULT_PORT 60000
#define DEFAULT_MAX_CLIENTS 20

namespace NetPhysics {
	/*
		Handles incoming connections and packets
	*/
	class ServerSystem : public System {
	public:

		ServerSystem() : System(NO_PARAMETERS) {}

		void init();
		void update();
		void startServer(bool userInputDetails);
		RakNet::RakPeerInterface* getRakPeerInstance();
		//Gets the packets received since the last update
		std::vector<PacketToBitStream> getPackets();

	private:

		//Pointer to the generated instance of RakPeerInterface
		RakNet::RakPeerInterface *rakPeerInstance;
		//What port the server runs on, only read at init, does not change during runtime
		uint32_t port;
		//Container for storing received packets.
		std::vector<PacketToBitStream> packetContainer;
		//maximum number of clients, only read at init, does not change during runtime
		uint32_t maxClients;
	};
}

#endif /* SERVER_SYSTEM_H_INCLUDED */