#ifndef PACKET_HANDLER_SYSTEM_H_INCLUDED
#define PACKET_HANDLER_SYSTEM_H_INCLUDED

#include "XLib.h"
#include "System.h"
#include "PacketToBitStream.h"

class EngineRegister;

class PacketHandlerSystem : public System {
public:
	void handle(EngineRegister &engineRegister, XLib::Vector<PacketToBitStream> packets);
};

#endif