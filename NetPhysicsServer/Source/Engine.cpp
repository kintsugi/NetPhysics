#include "Engine.h"
#include "Logger.h"
//System includes
#include "ServerSystem.h"
#include "NetworkSystem.h"
#include "PacketHandlerSystem.h"
#include "GameObject.h"
#include "PlayerStateComponent.h"
#include "ReplicationSystem.h"
#include "ReplicationComponent.h"

using namespace NetPhysics;

void Engine::init() {
	//Start the program clock.
	currentTime = RakNet::GetTimeUS();
	//Init the register and add all systems.
	reg.init();
	reg.addSystem(new ServerSystem(), SERVER_SYSTEM);
	reg.addSystem(new NetworkSystem(), NETWORK_SYSTEM);
	reg.addSystem(new PacketHandlerSystem(), PACKET_HANDLER_SYSTEM);
	reg.addSystem(new ReplicationSystem, REPLICATION_SYSTEM);

	handleManager = reg.getHandleManager();
	networkHandleManager = reg.getNetworkHandleManager();
	gameObjectManager = reg.getGameObjectManager();
	serverSystem = dynamic_cast<ServerSystem*>(reg.getSystem(SERVER_SYSTEM));
	packetHandlerSystem = dynamic_cast<PacketHandlerSystem*>(reg.getSystem(PACKET_HANDLER_SYSTEM));
	//Start the server!
	serverSystem->startServer(false);
	//Testing
	GameObject* testObject = NEW_GAME_OBJECT;
	ComponentManager* rCompM = reg.getComponentManager(REPLICATION_COMPONENT);
	ReplicationComponent* rComp = 
		new ReplicationComponent(*handleManager, *reg.getReplicaKeyManager());


}

void Engine::update() {
	static unsigned long long numIterations;
	static double time;
	dt = calculateDeltaTime();
	reg.update(dt);
	packetHandlerSystem->handle(reg, serverSystem->getPackets());
}

double Engine::calculateDeltaTime() {
	//Calculate the dt between last server tick
	lastTime = currentTime;
	currentTime = RakNet::GetTimeUS();
	return (currentTime - lastTime) / 1000000.0;
}

double Engine::getDeltaTime() {
	return dt;
}
