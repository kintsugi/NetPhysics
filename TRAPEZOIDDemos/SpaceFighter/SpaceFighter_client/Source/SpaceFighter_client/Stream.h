#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"

class StreamFormatter;

enum StreamType {
	DEFAULT_TYPE,
};

struct StreamData {
	StreamType type;
	TSharedPtr<RakNet::BitStream> formattedBitStream;
};

/*
Container for BitStreams meant for NetworkComponents.
BitStreams for NetworkComponents have a MessageID of NETWORK_COMPONENT_MESSAGE
followed by a Handle object.
Designed to cut the fluff off the a BitStream so other systems can read
data without having to now what identifying variables are there.
You can change how the formatter handles the stream by passing
a subclass of StreamFormatter overloading the virtual function format
You can also change the StreamData struct by casting another struct to it
and then casting it back.
*/
class Stream {
public:
	Stream(TSharedPtr<RakNet::BitStream> inBitStream, StreamFormatter* formatter);
	~Stream();
	StreamData* getStreamData();
private:
	StreamData* streamData;
};