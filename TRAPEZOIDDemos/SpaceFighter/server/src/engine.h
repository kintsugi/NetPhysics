#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <iostream>

//Manager includes
#include "gameobjectmanager.h"
#include "physicsmanager.h"
#include "networkmanager.h"
#include "clientmanager.h"

//System includes
#include "serversystem.h"
#include "physicssystem.h"
#include "networksystem.h"
#include "clientsystem.h"

/*
	Main system class. Handles and updates all managers and server.
*/

class Engine {
public:
	Engine();
	void update();
private:
	//Managers
	HandleManager handleManager;
	GameObjectManager gameObjectManager;
	PhysicsManager physicsManager;
	NetworkManager networkManager;
	ClientManager clientManager; 

	//Systems
	ServerSystem serverSystem;
	PhysicsSystem physicsSystem;
	NetworkSystem networkSystem;
	ClientSystem clientSystem;

	//Utility functions
	void handlePackets(std::vector<std::shared_ptr<RakNet::Packet>> inBitStreams);
};

#endif