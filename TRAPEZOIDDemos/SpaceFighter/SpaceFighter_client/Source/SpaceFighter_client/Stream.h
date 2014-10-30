#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "StreamFormatter.h"


template<class T>
class Stream {
public:
	Stream() : streamPtr(NULL) {}
	Stream(TSharedPtr<RakNet::BitStream> inBitStream, TSharedPtr<StreamFormatter> formatter) :
		streamPtr((T*)formatter->format(inBitStream)) {
	}

	TSharedPtr<T> getStream();
private:
	TSharedPtr<T> streamPtr;
};