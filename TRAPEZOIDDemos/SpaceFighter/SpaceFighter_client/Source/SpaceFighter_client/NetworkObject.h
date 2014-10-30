#pragma once

#include "SpaceFighter_client.h"
#include "Handle.h"
#include "AllowWindowsPlatformTypes.h"
#include "RakNetTypes.h"
#include "HideWindowsPlatformTypes.h"


class HandleManager;
class NetworkComponent;

/*
	Abstract class for Unreal Engine Objects for networking.
	Unreal Engine actors inherit this object and override networkUpdate()
	to specify function.
	networkUpdate() is called whenever a bitstream containing a networkID
	of the Network Component is received by the server.
*/
class NetworkObject {
public:
	NetworkObject() : handleManager(NULL) {}
	~NetworkObject();
	void init(HandleManager* handleManagerPtr, Handle newNetCompHandle);

	Handle getHandle();
	NetworkComponent* getNetworkComponent();
	RakNet::NetworkID getNetworkID();
	bool setNetworkID(RakNet::NetworkID networkID);

	virtual void networkUpdate() = 0;

private:
	HandleManager* handleManager;
	Handle handle;
	Handle networkComponentHandle;
};