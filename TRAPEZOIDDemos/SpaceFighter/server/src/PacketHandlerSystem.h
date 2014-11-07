#ifndef PACKET_HANDLER_SYSTEM_H_INCLUDED
#define PACKET_HANDLER_SYSTEM_H_INCLUDED

#include <vector>
#include "packettobitstream.h"

class EngineRegister;

class PacketHandlerSystem {
public:
	void handle(EngineRegister &engineRegister, std::vector<PacketToBitStream> packets);
};

#endif