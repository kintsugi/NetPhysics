#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#include <memory>
#include "NetworkIDObject.h"
#include "BitStream.h"

/*
	Class for handling inbound and outbound data for an entity between the client and the server.
	Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent : public RakNet::NetworkIDObject {
public:
	/*
		@param peer pointer to the server instance of RakNet
		@param guid the guid of the client
	*/
	NetworkComponent(RakNet::RakPeerInterface* peer, RakNet::NetworkIDManager* manager, RakNet::RakNetGUID connection) : out(peer), guid(connection){
		SetNetworkIDManager(manager);
	}
	RakNet::RakNetGUID getGUID() {return guid;}
	RakNet::RakPeerInterface* getRakNetInstance() {return out;}
	std::unique_ptr<RakNet::BitStream> in;
private:
	RakNet::RakPeerInterface* out;
	RakNet::RakNetGUID guid;
};


#endif