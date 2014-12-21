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
	template<class T>
	class Stream {
	public:

		Stream() : streamPtr(nullptr) {}
		Stream(
			std::shared_ptr<RakNet::BitStream> inBitStream,
			std::shared_ptr<StreamFormatter> formatter)
			: streamPtr((T*)formatter->format(inBitStream))
		{}

		std::shared_ptr<T> getStream();

	private:

		std::shared_ptr<T> streamPtr;
	};
}


#endif