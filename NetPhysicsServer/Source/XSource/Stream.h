#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef STREAM_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
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

		Stream() : streamPtr(NULL) {}
		Stream(XLib::SharedPtr<RakNet::BitStream> inBitStream,
			   XLib::SharedPtr<StreamFormatter> formatter) :
			   streamPtr((T*)formatter->format(inBitStream)) {}

		XLib::SharedPtr<T> getStream();

	private:

		XLib::SharedPtr<T> streamPtr;
	};
}


#endif