#include "NetPhysicsClient.h"
#include "ClientEngine.h"

//System includes
#include "ConnectionSystem.h"
#include "XSource/PacketHandlerSystem.h"

//Test includes
#include "AllowWindowsPlatformTypes.h"
#include "RakPeerInterface.h"
#include "HideWindowsPlatformTypes.h"
#include "XSource/GameObject.h"
#include "XSource/GameObjectManager.h"
#include "XSource/Logger.h"

using namespace NetPhysics;

void ClientEngine::init(UWorld* world) {
	engineRegister.init();
	engineRegister.setWorld(world);
	engineRegister.addSystem(new ConnectionSystem(), CONNECTION_SYSTEM);
	engineRegister.addSystem(new PacketHandlerSystem(), PACKET_HANDLER_SYSTEM);

	handleManager = engineRegister.getHandleManager();
	networkHandleManager = engineRegister.getNetworkHandleManager();
	connectionSystem = (ConnectionSystem*)engineRegister.getSystem(CONNECTION_SYSTEM);
	packetHandlerSystem = (PacketHandlerSystem*)engineRegister.getSystem(PACKET_HANDLER_SYSTEM);
	DEBUG_LOG(LOG_MSG, "RakNet attempting to connect to localhost on port 60000");
	connectionSystem->getRakPeerInstance()->Connect("localhost", 60000, 0, 0);
}

void ClientEngine::update(float dt) {
	engineRegister.update((double)dt);
	packetHandlerSystem->handle(engineRegister, connectionSystem->getPackets());
}