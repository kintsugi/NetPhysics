#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#include <memory>
#include "NetworkIDObject.h"
#include "BitStream.h"
#include "handle.h"

/*
	Class for handling inbound and outbound data for an entity between the client and the server.
	Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent : public RakNet::NetworkIDObject {
public:
	/*
		@param peer pointer to the server instance of RakNet
		@param manager pointer to a NetworkIDManager object for this object
		@param guid the guid of the owning client.
	*/
	NetworkComponent(RakNet::RakPeerInterface* peer, RakNet::NetworkIDManager* manager) : RakNet(peer){
		SetNetworkIDManager(manager); test = 0;
	}

	RakNet::RakPeerInterface* getRakNetInstance() {return RakNet;}
	std::unique_ptr<RakNet::BitStream> in;
	Handle getHandle() {return handle;}
	void setHandle(Handle newHandle)  {handle = newHandle;}
	int test;
private:
	Handle handle;
	RakNet::RakPeerInterface* RakNet;
};


#endif