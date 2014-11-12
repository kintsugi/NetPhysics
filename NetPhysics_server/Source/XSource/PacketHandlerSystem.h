#ifndef PACKET_HANDLER_SYSTEM_H_INCLUDED
#define PACKET_HANDLER_SYSTEM_H_INCLUDED

#ifdef CLIENT
	#undef PACKET_HANDLER_SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysics_client.h"
#endif /* CLIENT */

#include "XLib.h"
#include "System.h"
#include "PacketToBitStream.h"

class EngineRegister;

class PacketHandlerSystem : public System {
public:
	void handle(EngineRegister &engineRegister, XLib::Vector<PacketToBitStream> packets);
};

#endif