#ifndef PACKET_TO_BIT_STREAM_H_INCLUDED
#define PACKET_TO_BIT_STREAM_H_INCLUDED

#ifdef CLIENT
	#undef PACKET_TO_BIT_STREAM_H_INCLUDED	
	#pragma once
	#include "NetPhysics_client.h"
#endif /* CLIENT */
#include "XLib.h"
#ifdef CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* CLIENT */
	#include "BitStream.h"
#ifdef CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* CLIENT */
#include "RakNetTypes.h"

struct PacketToBitStream {
	PacketToBitStream(RakNet::Packet* packet);
	RakNet::RakNetGUID guid;
	RakNet::MessageID messageID;
	XLib::SharedPtr<RakNet::BitStream> bitStream;
};

#endif