#include "streamformatter.h"

StreamData* StreamFormatter::format(std::shared_ptr<RakNet::BitStream> inBitStream) {
	inBitStream->ResetReadPointer();
	StreamData* ret = new StreamData();
	inBitStream->IgnoreBytes(sizeof(RakNet::MessageID) + sizeof(Handle));
	inBitStream->Read(ret->type);
	RakNet::BitSize_t remainingBits = inBitStream->GetNumberOfUnreadBits();
	ret->formattedBitStream = std::shared_ptr<RakNet::BitStream>(new RakNet::BitStream());
	inBitStream->Read(ret->formattedBitStream.get(), remainingBits);
	return ret;
}