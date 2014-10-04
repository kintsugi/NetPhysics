#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "RakPeerInterface.h"

class NetworkComponent;

/*
	Player object encapsulates data relating the client connected to their game
	entities. Allows for easy access to a client's game state through their
	network component.
*/
class Player {
public:
	Player(RakNet::RakNetGUID ownerGuid, NetworkComponent* netComp) : guid(ownerGuid), net(netComp){}

private:
	RakNet::RakNetGUID guid;
	NetworkComponent* net;
};

#endif