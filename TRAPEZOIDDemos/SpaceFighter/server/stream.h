#ifndef STREAM_H_INCLUDED
#define STREAM_H_INCLUDED

#include <memory>
#include <vector>
#include "BitStream.h"
#include "handle.h"

/*
	Still in testing
	Utility class for RakNet Bitstreams
	Allows for easy linking to components through handles and
	removes the need to read identifiers from the Bitstream
*/

enum StreamType {
	UNASSIGNED_TYPE,
};

struct StreamData {
	Handle handle;
	StreamType type;
	std::shared_ptr<RakNet::BitStream> formattedStream;
};

class Stream {
public:
	Stream(std::shared_ptr<RakNet::BitStream> inStream, StreamFormatter* formatter);
	~Stream();
	StreamData* getStreamData();
private:
	StreamData* streamData;
};

class StreamFormatter {
public:
	virtual StreamData* format(std::shared_ptr<RakNet::BitStream> inStream);
};

#endif