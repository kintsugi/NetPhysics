#include "Engine.h"
//System includes
#include "ServerSystem.h"
#include "NetworkSystem.h"
#include "PacketHandlerSystem.h"
#include "ClientSystem.h"

using namespace NetPhysics;

void Engine::init() {
	//Start the program clock.
	currentTime = RakNet::GetTimeUS();
	//Init the register and add all systems.
	engineRegister.init();
	engineRegister.addSystem(new ServerSystem(), SERVER_SYSTEM);
	engineRegister.addSystem(new NetworkSystem(), NETWORK_SYSTEM);
	engineRegister.addSystem(new PacketHandlerSystem(), PACKET_HANDLER_SYSTEM);
	engineRegister.addSystem(new ClientSystem(), CLIENT_SYSTEM);

	handleManager = engineRegister.getHandleManager();
	networkHandleManager = engineRegister.getNetworkHandleManager();
	gameObjectManager = engineRegister.getGameObjectManager();
	serverSystem = dynamic_cast<ServerSystem*>(engineRegister.getSystem(SERVER_SYSTEM));
	packetHandlerSystem = dynamic_cast<PacketHandlerSystem*>(engineRegister.getSystem(PACKET_HANDLER_SYSTEM));
	
	//Start the server!
	serverSystem->startServer(false);
}

void Engine::update() {
	dt = calculateDeltaTime();
	engineRegister.update(dt);
	packetHandlerSystem->handle(engineRegister, serverSystem->getPackets());
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
