#ifndef STREAM_FORMATTER_H_INCLUDED
#define STREAM_FORMATTER_H_INCLUDED

#include <memory>
#include "BitStream.h"
#include "stream.h"

class StreamFormatter {
public:
	virtual StreamData* format(std::shared_ptr<RakNet::BitStream> inStream);
};

#endif