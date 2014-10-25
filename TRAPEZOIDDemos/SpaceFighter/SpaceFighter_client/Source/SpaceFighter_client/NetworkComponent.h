#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "Handle.h"

class HandleManager;

/*
Class for handling inbound and outbound data for an entity between the client and the server.
Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent {
public:
	/*
	@param peer pointer to the server instance of RakNet
	@param manager pointer to a NetworkIDManager object for this object
	@param guid the guid of the owning client.
	*/
	NetworkComponent(HandleManager* handleManager, RakNet::RakPeerInterface* peer);

	void addStream(TSharedPtr<RakNet::BitStream> inStream);
	TArray<TSharedPtr<RakNet::BitStream>> getReceivedStreams();
	RakNet::RakPeerInterface* getRakNetInstance();
	Handle getHandle();
private:
	Handle handle;
	RakNet::RakPeerInterface* RakNetInstance;
	TArray<TSharedPtr<RakNet::BitStream>> receivedStreams;
};
