#include "stream.h"
#include "streamformatter.h"

Stream::Stream(std::shared_ptr<RakNet::BitStream> inStream, StreamFormatter* formatter = NULL) {
	
	if (formatter)
		streamData = formatter->format(inStream);
	else {
		streamData = StreamFormatter().format(inStream);
	}
}

Stream::~Stream() {
	delete streamData;
}

StreamData* Stream::getStreamData() {
	return streamData;
}