#ifndef STREAM_FORMATTER_H_INCLUDED
#define STREAM_FORMATTER_H_INCLUDED

#include <memory>
#include "BitStream.h"

class StreamFormatter {
public:
	virtual void* format(XLib::SharedPtr<RakNet::BitStream> inStream) = 0;
};

#endif