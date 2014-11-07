#include "packethandlersystem.h"
#include <iostream>
#include "engineregister.h"
#include "MessageIdentifiers.h"
#include "networkmessage.h"
#include "clientsystem.h"
#include "networksystem.h"
#include "networkhandlemanager.h"

void PacketHandlerSystem::handle(EngineRegister &engineRegister, XLib::Vector<PacketToBitStream> packets) {
	//Get systems and managers needed from register
	RakNet::NetworkIDManager *networkIDManager = engineRegister.getManager<RakNet::NetworkIDManager>(NETWORK_HANDLE_MANAGER);
	ClientSystem *clientSystem = engineRegister.getSystem<ClientSystem>(CLIENT_SYSTEM);
	NetworkSystem *networkSystem = engineRegister.getSystem<NetworkSystem>(NETWORK_SYSTEM);

	for (auto iter = packets.begin(); iter != packets.end(); iter++) {
		switch (iter->messageID) {
			case ID_NEW_INCOMING_CONNECTION: {
				std::cout << std::endl << "A client has connected. GUID: " << iter->guid.ToString();
				clientSystem->initializeClient(engineRegister,
											  iter->guid);
				break;
			}
			case NetworkMessage::ID::NETWORK_COMPONENT_MESSAGE: {
				networkSystem->sendToNetworkComponent(*networkIDManager, *iter);
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
}