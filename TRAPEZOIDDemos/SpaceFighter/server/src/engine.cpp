#include "engine.h"
#include "MessageIdentifiers.h"
#include "networkmessage.h"
#include <memory>
#include "RakNetTypes.h"

Engine::Engine() : postInitReady(false) {
	init();

}

void Engine::update() {
	//The ServerSystem needs to be updated before any other process.
	serverSystem.update();
	//Get the delta time.
	double dt = serverSystem.getDeltaTime();
	updateManagers(dt);
	updateSystems(dt);
}

void Engine::init() {
	//ServerSystem + EngineRegister has to be started before calling initManagers/Systems().
	serverSystem.startServer(false);
	engineRegister.init(serverSystem.getRakNetInstance());
	postInitReady = true;
	initManagers();
	initSystems();
}

void Engine::initManagers() {
	//Register managers. 
	if (postInitReady) {
		engineRegister.addManager(&handleManager, HANDLE_MANAGER);
		engineRegister.addManager(&networkHandleManager, NETWORK_HANDLE_MANAGER);
		engineRegister.addManager(&gameObjectManager, GAME_OBJECT_MANAGER);
		engineRegister.addManager(&physicsManager, PHYSICS_MANAGER);
		engineRegister.addManager(&networkManager, NETWORK_MANAGER);
		engineRegister.addManager(&clientManager, CLIENT_MANAGER);
		engineRegister.addManager(&playerStateManager, PLAYER_STATE_MANAGER);
		engineRegister.addManager(&timerManager, TIMER_MANAGER);
	}
}

void Engine::initSystems() {
	if (postInitReady) {
		//Register systems.
		engineRegister.addSystem(&serverSystem, SERVER_SYSTEM);
		engineRegister.addSystem(&physicsSystem, PHYSICS_SYSTEM);
		engineRegister.addSystem(&networkSystem, NETWORK_SYSTEM);
		engineRegister.addSystem(&clientSystem, CLIENT_SYSTEM);
		engineRegister.addSystem(&playerInitSystem, PLAYER_INIT_SYSTEM);
		engineRegister.addSystem(&packetHandlerSystem, PACKET_HANDLER_SYSTEM);
	}
}

void Engine::updateManagers(double dt) {
	//Update managers
	gameObjectManager.update(handleManager);
	physicsManager.update(handleManager);
	networkManager.update(handleManager);
	clientManager.update(handleManager);
	playerStateManager.update(handleManager);
	timerManager.update(handleManager, dt);
}

void Engine::updateSystems(double dt) {
	//Update systems. Process game state/data first then logic systems
	physicsSystem.update((float)dt);
	playerInitSystem.update(engineRegister);
	//Handle incoming packets.
	packetHandlerSystem.handle(engineRegister, serverSystem.getPackets());
}