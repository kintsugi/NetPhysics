#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"

class StreamFormatter {
public:
	virtual void* format(TSharedPtr<RakNet::BitStream> inStream) = 0;
};