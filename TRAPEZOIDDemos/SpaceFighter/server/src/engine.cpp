#include "engine.h"
#include "networkmessages.h"

#include <memory>
#include "RakNetTypes.h"

Engine::Engine() {
	serverSystem.startServer(false);
}

void Engine::update() {
	//Update managers that continuous updating
	gameObjectManager.update(handleManager);
	physicsManager.update(handleManager);
	networkManager.update(handleManager);
	clientManager.update(handleManager);

	//Update systems that need continuous updating
	physicsSystem.update((float)serverSystem.getDeltaTime());

	//handle the incoming streams
	handlePackets(serverSystem.getPackets());
}

void Engine::handlePackets(std::vector<std::shared_ptr<RakNet::Packet>> packets) {
	for (auto iter = packets.begin(); iter != packets.end(); iter++) {
		//Read the first bytes as a NetworkMessage to determine action
		RakNet::Packet* packet = iter->get();
		std::cout << std::endl << (int)packet->data[0];
		switch (packet->data[0]) {
			case ID_NEW_INCOMING_CONNECTION: {
				clientSystem.InitializeClient(handleManager, gameObjectManager, clientManager, packet->guid);
					break;
			}
			case NETWORK_COMPONENT_MESSAGE: {
				networkSystem.sendToNetworkComponent(handleManager, *iter);
				break;
			}
		}
	}	
}