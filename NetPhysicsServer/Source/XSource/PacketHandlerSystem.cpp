#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#ifdef NET_PHYSICS_SERVER
	#include <iostream>
#endif /* NET_PHYSICS_SERVER */
#include "PacketHandlerSystem.h"
#include "Register.h"
#include "MessageIdentifiers.h"
#include "NetworkMessage.h"
#include "NetworkSystem.h"
#include "NetworkHandleManager.h"
#include "Logger.h"

using namespace NetPhysics;

void PacketHandlerSystem::handle(Register &reg,
	std::vector<PacketToBitStream> packets)
{
#ifdef NET_PHYSICS_SERVER
	//Get systems and managers needed from register
	NetworkHandleManager* networkHandleManager = reg.getNetworkHandleManager();
	NetworkSystem *networkSystem = (NetworkSystem*)reg.getSystem(NETWORK_SYSTEM);

	for (auto iter = packets.begin(); iter != packets.end(); iter++) {
		switch (iter->messageID) {
			case ID_NEW_INCOMING_CONNECTION: {
				LOG(LOG_MSG, "A client has connected. GUID: " + std::string(iter->guid.ToString()));
				break;
			}
			case NetworkMessage::ID::NETWORK_COMPONENT_MESSAGE: {
				networkSystem->sendToNetworkComponent(*networkHandleManager, *iter);
				break;
			}
			case NetworkMessage::CLIENT_DISCONNECT: {
			}
		}
	}
#endif
}