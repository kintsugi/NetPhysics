#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

#include <memory>
#include <vector>
#include "BitStream.h"
#include "handle.h"

class StreamFormatter;

enum StreamType {
	DEFAULT_TYPE,
};

struct StreamData {
	StreamType type;
	std::shared_ptr<RakNet::BitStream> formattedBitStream;
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
	Stream(std::shared_ptr<RakNet::BitStream> inBitStream, StreamFormatter* formatter);
	~Stream();
	StreamData* getStreamData();
private:
	StreamData* streamData;
};



#endif