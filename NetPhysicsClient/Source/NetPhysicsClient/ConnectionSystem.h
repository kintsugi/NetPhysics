#pragma once
#include <vector>
#include "NetPhysicsClient.h"
#include "XSource/System.h"
#include "XSource/PacketToBitStream.h"

namespace RakNet {
	class RakPeerInterface;
}

namespace NetPhysics {
	class ConnectionSystem : public System {
	public:

		~ConnectionSystem();

		void init();
		RakNet::RakPeerInterface* getRakPeerInstance();
		std::vector<PacketToBitStream> getPackets();

	private:

		RakNet::RakPeerInterface *rakPeerInstance;
	};
}