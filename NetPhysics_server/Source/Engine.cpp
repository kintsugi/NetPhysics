#include "engine.h"
#include "MessageIdentifiers.h"
#include "NetworkMessage.h"
#include "ServerSystem.h"
#include "PacketHandlerSystem.h"
#include "NetworkSystem.h"
#include "ClientSystem.h"

Engine::Engine() {

}

void Engine::update() {
	dt = serverSystem->getDeltaTime();
	engineRegister.update(dt);
	packetHandlerSystem->handle(engineRegister, serverSystem->getPackets());
}

void Engine::init() {
	engineRegister.init();
	engineRegister.initSystem(new PacketHandlerSystem(), PACKET_HANDLER_SYSTEM);
	engineRegister.initSystem(new NetworkSystem(), NETWORK_SYSTEM);
	engineRegister.initSystem(new ClientSystem(), CLIENT_SYSTEM);

	handleManager = engineRegister.getHandleManager();
	networkHandleManager = engineRegister.getNetworkHandleManager();
	gameObjectManager = engineRegister.getGameObjectManager();
	
	serverSystem = (ServerSystem*)engineRegister.getSystem(SERVER_SYSTEM);
	packetHandlerSystem = (PacketHandlerSystem*)engineRegister.getSystem(PACKET_HANDLER_SYSTEM);
}