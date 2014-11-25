#pragma once
#include "NetPhysicsClient.h"
#include "XSource/XLib.h"
#include "XSource/System.h"
#include "XSource/PacketToBitStream.h"

namespace RakNet {
	class RakPeerInterface;
}

class ConnectionSystem : public System {
public:

	void init();
	RakNet::RakPeerInterface* getRakPeerInstance();
	XLib::Vector<PacketToBitStream> getPackets();

private:

	RakNet::RakPeerInterface *rakPeerInstance;
};