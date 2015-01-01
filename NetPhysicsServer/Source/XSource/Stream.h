#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef STREAM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#ifdef NET_PHYSICS_CLIENT
	#include "AllowWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
	#include "BitStream.h"
#ifdef NET_PHYSICS_CLIENT
	#include "HideWindowsPlatformTypes.h"
#endif /* NET_PHYSICS_CLIENT */
#include "StreamFormatter.h"

namespace NetPhysics {
	template<typename T>
	struct Stream {
		Stream() : streamPtr(nullptr) {}
		Stream(
			RakNet::BitStream &inBitStream,
			StreamFormatter<T> *formatter)
			: streamPtr(formatter->format(inBitStream))
		{}
		std::shared_ptr<T> streamPtr;
	};
}


#endif