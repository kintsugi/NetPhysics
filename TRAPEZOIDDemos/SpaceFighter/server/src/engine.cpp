#include "engine.h"
#include "networkmessages.h"
#include <memory>

Engine::Engine() {
	serverSystem.startServer(false);
}

void Engine::update() {
	//Update managers that continuous updating
	gameObjectManager.update(&handleManager);
	//physicsManager.update(&handleManager);
	networkManager.update(&handleManager);
	clientManager.update(&handleManager);

	//Update systems that need continuous updating
	physicsSystem.update((float)serverSystem.getDeltaTime());

	//handle the incoming streams
	handleStreams(serverSystem.getStreams());
}

void Engine::handleStreams(std::vector<std::shared_ptr<RakNet::BitStream>> inStreams) {
	for (auto iter = inStreams.begin(); iter != inStreams.end(); iter++) {
		//Read the first bytes as a NetworkMessage to determine action
		NetworkMessage networkMessage = NetworkMessage::INVALID_MESSAGE;
		iter->get()->Read(networkMessage);
		switch (networkMessage) {
		case ID_NEW_INCOMING_CONNECTION:
			std::cout << std::endl << "A client has connected";
		}
	}
	
}