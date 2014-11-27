#ifndef PACKET_HANDLER_SYSTEM_H_INCLUDED
#define PACKET_HANDLER_SYSTEM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef PACKET_HANDLER_SYSTEM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#include "XLib.h"
#include "System.h"
#include "PacketToBitStream.h"

namespace NetPhysics {
	class Register;

	class PacketHandlerSystem : public System {
	public:
		void handle(Register &engineRegister,
					XLib::Vector<PacketToBitStream> packets);
	};
}

#endif