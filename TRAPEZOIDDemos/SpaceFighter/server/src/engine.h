#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED


#include "EngineRegister.h"

//Manager includes
#include "networkhandlemanager.h"
#include "gameobjectmanager.h"

class HandleManager;
class NetworkHandleManager;
class GameObjectManager;

class ServerSystem;
class PacketHandlerSystem;

/*
	Main program class. Handles and updates all managers and systems.
*/
class Engine {
public:

	Engine();
	void init();
	void update();

private:

	//Engine register to encapsulate RakNet, managers, and system
	EngineRegister engineRegister;

	//Ptrs to frequently used objects
	HandleManager *handleManager;
	NetworkHandleManager *networkHandleManager;
	GameObjectManager *gameObjectManager;

	//Systems used every tick
	ServerSystem *serverSystem;
	PacketHandlerSystem* packetHandlerSystem;

	//Time since last update;
	double dt;

};

#endif