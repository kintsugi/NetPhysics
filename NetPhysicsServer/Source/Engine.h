#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "Register.h"
//Time includes
#include "RakNetTime.h"
//Manager includes & forward declarations
#include "NetworkHandleManager.h"
#include "GameObjectManager.h"

/*
	Main program class. Handles and updates all managers and systems.
*/
namespace NetPhysics {
	//Namespace Forward Declarations.
	class HandleManager;
	class NetworkHandleManager;
	class GameObjectManager;
	class ServerSystem;
	class PacketHandlerSystem;

	class Engine {
	public:

		void init();
		void update();

		//Returns time since last update, used as clock for whole program.
		double calculateDeltaTime();

		//Does not calculate, only returns the value of dt.
		double getDeltaTime();

	private:

		//Engine register to encapsulate RakNet, managers, and system
		Register reg;

		//Ptrs to frequently used objects
		HandleManager *handleManager;
		NetworkHandleManager *networkHandleManager;
		GameObjectManager *gameObjectManager;

		//Systems used every tick
		ServerSystem *serverSystem;
		PacketHandlerSystem* packetHandlerSystem;

		//Delta Time
		double dt;
		//Current time the engine is on.
		RakNet::TimeUS currentTime;
		//Previous time.
		RakNet::TimeUS lastTime;
	};
}
#endif