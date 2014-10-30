#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "HideWindowsPlatformTypes.h"

struct PacketToBitStream {
	PacketToBitStream(RakNet::Packet* packet);
	RakNet::RakNetGUID guid;
	RakNet::MessageID messageID;
	TSharedPtr<RakNet::BitStream> bitStream;
};