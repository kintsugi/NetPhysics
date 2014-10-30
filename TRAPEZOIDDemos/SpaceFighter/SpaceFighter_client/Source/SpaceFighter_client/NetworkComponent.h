#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "NetworkIDObject.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "Stream.h"
#include "Handle.h"

class HandleManager;

/*
Class for handling inbound and outbound data for an entity between the client and the server.
Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent : public RakNet::NetworkIDObject {
public:

	NetworkComponent(HandleManager& handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer);
	NetworkComponent(HandleManager& handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer, StreamFormatter* formatter);

	void setFormatter(StreamFormatter* formatter);

	void addBitStream(TSharedPtr<RakNet::BitStream> inBS);

	TArray<Stream> getAllStreams();
	TArray<Stream> getStreamsOfType(StreamType type);

	void removeAllStreams();
	void removeStreamsOfType(StreamType type);

	RakNet::RakPeerInterface* getRakPeerInstance();
	Handle getHandle();

private:
	Handle handle;
	RakNet::RakPeerInterface* RakPeerInstance;
	StreamFormatter* formatter;
	TArray<Stream> streams;
};
