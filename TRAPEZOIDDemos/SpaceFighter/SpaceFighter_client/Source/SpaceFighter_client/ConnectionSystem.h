#pragma once

#include "SpaceFighter_client.h"
#include <vector>
#include <memory>
#include "AllowWindowsPlatformTypes.h"
#include "RakPeerInterface.h"
#include "HideWindowsPlatformTypes.h"

/*
	Manager for connecting and communicating to the server.
*/
class ConnectionSystem
{
public:
	ConnectionSystem();
	void receivePackets();
	void connect();
	void connect(FString ipAddress, int port);
	TArray<TSharedPtr<RakNet::BitStream>> getStreams();
	RakNet::RakPeerInterface* getRakNetInstance();
private:
	//Pointer to the generated instance of RakPeerInterface
	RakNet::RakPeerInterface *peer;
	FString ipAddress;
	int port;
	TArray<TSharedPtr<RakNet::BitStream>> receivedStreams;
};
