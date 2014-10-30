#include "engine.h"
#include "networkmessages.h"
#include <memory>
#include "RakNetTypes.h"

Engine::Engine() {
	serverSystem.startServer(false);
	managerRegister.peer = serverSystem.getRakNetInstance();
	//Register managers.
	managerRegister.add(&handleManager, HANDLE_MANAGER);
	managerRegister.add(&networkIDManager, NETWORK_ID_MANAGER);
	managerRegister.add(&gameObjectManager, GAME_OBJECT_MANAGER);
	managerRegister.add(&physicsManager, PHYSICS_MANAGER);
	managerRegister.add(&networkManager, NETWORK_MANAGER);
	managerRegister.add(&clientManager, CLIENT_MANAGER);
	managerRegister.add(&playerStateManager, PLAYER_STATE_MANAGER);
	managerRegister.add(&timerManager, TIMER_MANAGER);
}

void Engine::update() {
	//The ServerSystem needs to be updated before any other process.
	serverSystem.update();
	//Get the delta time.
	double dt = serverSystem.getDeltaTime();

	//Update managers
	gameObjectManager.update(handleManager);
	physicsManager.update(handleManager);
	networkManager.update(handleManager);
	clientManager.update(handleManager);
	playerStateManager.update(handleManager);
	timerManager.update(handleManager, dt);

	//Update systems
	physicsSystem.update((float)dt);
	gameStateSystem.update(managerRegister);

	NetworkComponent* testComp = new NetworkComponent(handleManager, networkIDManager, serverSystem.getRakNetInstance(), new TestFormatter());
	std::shared_ptr<RakNet::BitStream> testBS(new RakNet::BitStream());
	testBS->Write((RakNet::MessageID)NETWORK_COMPONENT_MESSAGE);
	testBS->Write("Hello World");
	testComp->addBitStream(testBS);
	Stream<TestStreamData> testStream = testComp->popStream<TestStreamData>();
	//Handle incoming packets.
	handlePackets(serverSystem.getPackets());
}

void Engine::handlePackets(std::vector<PacketToBitStream> packets) {
	for (auto iter = packets.begin(); iter != packets.end(); iter++) {
		
		switch (iter->messageID) {
			case ID_NEW_INCOMING_CONNECTION: {
				clientSystem.initializeClient(managerRegister,
											  serverSystem.getRakNetInstance(), 
											  iter->guid);
				break;
			}
			case NETWORK_COMPONENT_MESSAGE: {
				networkSystem.sendToNetworkComponent(networkIDManager, *iter);
				break;
			}
		}
	}	
}

void* TestFormatter::format(std::shared_ptr<RakNet::BitStream> inStream) {
	inStream->ResetReadPointer();
	TestStreamData* ret = new TestStreamData();
	inStream->Read(ret->messageID);
	inStream->ResetReadPointer();
	ret->bitStream = inStream;
	return ret;
}