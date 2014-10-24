#include "stream.h"

Stream::Stream(std::shared_ptr<RakNet::BitStream> inStream, StreamFormatter* formatter = NULL) {
	
	if (formatter)
		streamData = new StreamData(formatter->format(inStream));
	else {
		streamData = new StreamData(StreamFormatter().format(inStream));
	}
}

Stream::~Stream() {
	delete streamData;
}

StreamData* Stream::getStreamData() {
	return streamData;
}

StreamData* StreamFormatter::format(std::shared_ptr<RakNet::BitStream> inStream) {
	inStream->ResetReadPointer();
	StreamData* ret = new StreamData();
	inStream->IgnoreBytes(sizeof(RakNet::MessageID));
	inStream->Read(ret->handle);
	inStream->Read(ret->type);
	RakNet::BitSize_t remainingBits = inStream->GetNumberOfUnreadBits();
	ret->formattedStream = std::shared_ptr<RakNet::BitStream>(new RakNet::BitStream());
	ret->formattedStream->Write(inStream.get(), remainingBits);
	return ret;
}