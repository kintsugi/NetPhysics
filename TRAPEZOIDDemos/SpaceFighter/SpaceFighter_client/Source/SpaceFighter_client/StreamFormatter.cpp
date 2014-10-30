#include "SpaceFighter_client.h"
#include "StreamFormatter.h"
#include "Handle.h"


StreamData* StreamFormatter::format(TSharedPtr<RakNet::BitStream> inBitStream) {
	inBitStream->ResetReadPointer();
	StreamData* ret = new StreamData();
	inBitStream->IgnoreBytes(sizeof(RakNet::MessageID) + sizeof(RakNet::NetworkID));
	inBitStream->Read(ret->type);
	RakNet::BitSize_t remainingBits = inBitStream->GetNumberOfUnreadBits();
	ret->formattedBitStream = TSharedPtr<RakNet::BitStream>(new RakNet::BitStream());
	inBitStream->Read(ret->formattedBitStream.Get(), remainingBits);
	return ret;
}