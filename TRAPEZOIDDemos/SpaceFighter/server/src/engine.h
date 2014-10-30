#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <iostream>
#include "managerregister.h"

//Manager includes
#include "NetworkIDManager.h"
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
#include "gamestatesystem.h"

/*
	Main system class. Handles and updates all managers and server.
*/

class Engine {
public:
	Engine();
	void update();
private:
	ManagerRegister managerRegister;

	//Managers
	HandleManager handleManager;
	RakNet::NetworkIDManager networkIDManager;
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
	GameStateSystem gameStateSystem;

	//Utility functions
	void handlePackets(std::vector<std::shared_ptr<RakNet::Packet>> packets);
};

#endif