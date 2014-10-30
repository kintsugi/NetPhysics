#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "stream.h"

class StreamFormatter {
public:
	virtual StreamData* format(TSharedPtr<RakNet::BitStream> inStream);
};