#ifndef STREAM_FORMATTER_H_INCLUDED
#define STREAM_FORMATTER_H_INCLUDED

#ifdef CLIENT
	#undef STREAM_FORMATTER_H_INCLUDED
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

#include "XLib.h"

namespace RakNet {
	class BitStream;
}

class StreamFormatter {
public:

	virtual void* format(XLib::SharedPtr<RakNet::BitStream> inStream) = 0;
};

#endif