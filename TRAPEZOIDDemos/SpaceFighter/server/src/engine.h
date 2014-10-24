#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <iostream>
#include "serversystem.h"
#include "gameobjectmanager.h"
#include "physicsmanager.h"
#include "physicssystem.h"
#include "networkmanager.h"
#include "clientmanager.h"


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

	void handleStreams(std::vector<std::shared_ptr<RakNet::BitStream>> inStreams);
};

#endif