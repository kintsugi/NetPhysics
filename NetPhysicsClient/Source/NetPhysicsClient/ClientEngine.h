#pragma once
#include "NetPhysicsClient.h"
#include "XSource/Register.h"

class UWorld;

namespace NetPhysics {
	class HandleManager;
	class NetworkHandleManager;
	class ConnectionSystem;
	class PacketHandlerSystem;
	class ClientEngine {
	public:

		void init(UWorld* world);
		void update(float dt);

	private:

		//Engine register to encapsulate RakNet, managers, and system
		Register engineRegister;

		//Ptrs to frequently used objects
		HandleManager *handleManager;
		NetworkHandleManager *networkHandleManager;

		//Systems used every tick
		ConnectionSystem* connectionSystem;
		PacketHandlerSystem* packetHandlerSystem;

	};
}