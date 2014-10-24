#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#include <vector>
#include <memory>
#include "BitStream.h"
#include "handle.h"

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

	void addStream(std::shared_ptr<RakNet::BitStream> inStream);
	std::vector<std::shared_ptr<RakNet::BitStream>> getReceivedStreams();
	
	RakNet::RakPeerInterface* getRakNetInstance();
	Handle getHandle();
private:
	Handle handle;
	RakNet::RakPeerInterface* RakNetInstance;
	std::vector<std::shared_ptr<RakNet::BitStream>> receivedStreams;
};


#endif