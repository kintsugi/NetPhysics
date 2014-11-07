#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED


#include "engineregister.h"

//Manager includes
#include "networkhandlemanager.h"
#include "gameobjectmanager.h"
#include "physicsmanager.h"
#include "networkmanager.h"
#include "clientmanager.h"
#include "playerstatemanager.h"
#include "timermanager.h"

//System includes
#include "serversystem.h"
#include "physicssystem.h"
#include "networksystem.h"
#include "clientsystem.h"
#include "playerinitsystem.h"
#include "packethandlersystem.h"

/*
	Main program class. Handles and updates all managers and systems.
*/

class Engine {
public:

	Engine();
	void update();

private:

	//Engine register to encapsulate RakNet, managers, and system
	EngineRegister engineRegister;

	//Managers
	HandleManager handleManager;
	NetworkHandleManager networkHandleManager;
	GameObjectManager gameObjectManager;
	PhysicsManager physicsManager;
	NetworkManager networkManager;
	ClientManager clientManager;
	PlayerStateManager playerStateManager;
	TimerManager timerManager;


	//Systems
	ServerSystem serverSystem;
	PhysicsSystem physicsSystem;
	NetworkSystem networkSystem;
	ClientSystem clientSystem;
	PlayerInitSystem playerInitSystem;
	PacketHandlerSystem packetHandlerSystem;

	//init functions
	void init();
	void initManagers();
	void initSystems();

	//Managers must be updated before systems
	void updateManagers(double dt);
	void updateSystems(double dt);

	//Utility functions
	void handlePackets(XLib::Vector<PacketToBitStream> packets);

	//False if the engine is not ready to start
	bool postInitReady;
};

#endif