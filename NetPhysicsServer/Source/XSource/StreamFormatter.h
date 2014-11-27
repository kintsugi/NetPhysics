#ifndef STREAM_FORMATTER_H_INCLUDED
#define STREAM_FORMATTER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef STREAM_FORMATTER_H_INCLUDED
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"

namespace RakNet {
	class BitStream;
}

namespace NetPhysics {
	class StreamFormatter {
	public:

		virtual void* format(XLib::SharedPtr<RakNet::BitStream> inStream) = 0;
	};
}

#endif