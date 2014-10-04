#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include <vector>
#include <iostream>
#include "server.h"
#include "gameobjectmanager.h"
#include "physicsmanager.h"
#include "physicssystem.h"
#include "networkmanager.h"

/*
	Main system class. Handles and updates all managers and server.
*/

class Engine : private Server {
public:
	Engine();
	void update();
private:
	//Managers
	HandleManager handleManager;
	RakNet::NetworkIDManager networkIDManager;
	GameObjectManager gameObjectManager;
	PhysicsManager physicsManager;
	NetworkManager networkManager;

	//Systems

};

#endif