#ifndef PACKET_TO_BIT_STREAM_H_INCLUDED
#define PACKET_TO_BIT_STREAM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef PACKET_TO_BIT_STREAM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
	#include "BitStream.h"
	#include "RakNetTypes.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include <memory>

namespace NetPhysics {
	struct PacketToBitStream {
		PacketToBitStream(RakNet::Packet* packet);
		RakNet::RakNetGUID guid;
		RakNet::MessageID messageID;
		std::shared_ptr<RakNet::BitStream> bitStream;
	};
}

#endif