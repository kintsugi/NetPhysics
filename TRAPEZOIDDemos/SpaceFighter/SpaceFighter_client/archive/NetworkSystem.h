#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "RakNetTypes.h"
#include "HideWindowsPlatformTypes.h"
#include "NetworkHandleManager.h"
#include "Handle.h"
#include "PacketToBitStream.h"

class HandleManager;
class NetworkHandleManager;
class NetworkObject;

class NetworkSystem {
public:
	void registerActor(HandleManager &handleManager, NetworkObject* networkObject);
	void sendToNetworkComponent(NetworkHandleManager &networkIDManager, HandleManager &handleManager, PacketToBitStream &packet);
private:
	TMap<NetworkKey, Handle> registeredActors;
};