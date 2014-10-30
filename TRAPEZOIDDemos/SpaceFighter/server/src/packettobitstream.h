#ifndef PACKET_TO_BIT_STREAM_H_INCLUDED
#define PACKET_TO_BIT_STREAM_H_INCLUDED

#include <memory>
#include "BitStream.h"
#include "RakNetTypes.h"

struct PacketToBitStream {
	PacketToBitStream(RakNet::Packet* packet);
	RakNet::RakNetGUID guid;
	RakNet::MessageID messageID;
	std::shared_ptr<RakNet::BitStream> bitStream;
};

#endif