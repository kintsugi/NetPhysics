#include "PacketHandlerSystem.h"

#ifdef CLIENT
	#include "NetPhysics_client.h"
#endif /* CLIENT */
#ifdef SERVER
	#include "ClientSystem.h"
#endif /* SERVER */
#include "EngineRegister.h"
#include "MessageIdentifiers.h"
#include "NetworkMessage.h"
#include "NetworkSystem.h"
#include "NetworkHandleManager.h"

void PacketHandlerSystem::handle(EngineRegister &engineRegister, XLib::Vector<PacketToBitStream> packets) {
#ifdef SERVER
	//Get systems and managers needed from register
	NetworkHandleManager* networkHandleManager = engineRegister.getNetworkHandleManager();
	ClientSystem *clientSystem = (ClientSystem*)engineRegister.getSystem(CLIENT_SYSTEM);
	NetworkSystem *networkSystem = (NetworkSystem*)engineRegister.getSystem(NETWORK_SYSTEM);

	for (auto iter = packets.begin(); iter != packets.end(); iter++) {
		switch (iter->messageID) {
			case ID_NEW_INCOMING_CONNECTION: {
				std::cout << std::endl << "A client has connected. GUID: " << iter->guid.ToString();
				clientSystem->initializeClient(engineRegister,
											  iter->guid);
				break;
			}
			case NetworkMessage::ID::NETWORK_COMPONENT_MESSAGE: {
				networkSystem->sendToNetworkComponent(*networkHandleManager, *iter);
				break;
			}
			case NetworkMessage::CLIENT_DISCONNECT: {
				iter->bitStream->ResetReadPointer();
				iter->bitStream->IgnoreBytes(sizeof(RakNet::MessageID));
				NetworkKey networkKey;
				iter->bitStream->Read(networkKey);
				clientSystem->removeClient(engineRegister, networkKey);
			}
		}
	}
#endif
}