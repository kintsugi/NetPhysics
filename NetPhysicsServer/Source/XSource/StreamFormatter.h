#ifndef STREAM_FORMATTER_H_INCLUDED
#define STREAM_FORMATTER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef STREAM_FORMATTER_H_INCLUDED
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */


namespace RakNet {
	class BitStream;
}

namespace NetPhysics {
	template <class T>
	class StreamFormatter {
	public:

		virtual T* format(RakNet::BitStream &inStream) = 0;
	};
}

#endif