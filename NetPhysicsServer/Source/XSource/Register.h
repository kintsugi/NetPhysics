#ifndef REGISTER_H_INCLUDED
#define REGISTER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REGISTER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#ifdef NET_PHYSICS_SERVER
#include "GameObjectManager.h"
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
#include "Engine/World.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
#include "HandleManager.h"
#include "NetworkHandleManager.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "ComponentType.h"
#include "SystemType.h"


namespace RakNet { 
	class RakPeerInterface;
}

namespace NetPhysics {
	class System;
	class Register {
	public:

		//Call at start of engine.
		void init();

		//Updates managers and systems.
		void update(const double dt);

#ifdef NET_PHYSICS_CLIENT
		void setWorld(UWorld* world);
		UWorld* getWorld();
#endif /* NET_PHYSICS_CLIENT */

		//Returns engine instance of the handle manager
		HandleManager* getHandleManager();

		//Returns the engine instance of the network handle manager
		NetworkHandleManager* getNetworkHandleManager();

		//Returns the engine instance of the game object manager
		GameObjectManager* getGameObjectManager();

		//Returns the engine instance of RakNetPeer
		RakNet::RakPeerInterface* getRakPeerInstance();

		/*
		Returns the specified component manager
		@param type the the type of component that the returned manager holds.
		*/
		ComponentManager* getComponentManager(ComponentType type);

		/*
		Returns the active system of that type. Returns null if the specified system
		is not active
		*/
		System* getSystem(SystemType type);

		/*
		Adds a system to the engine register. Adding an already placed system overwrites.
		@param newSystem pointer to an object inheriting System
		@param type enum identifier to mark the system
		*/
		void addSystem(System* newSystem,
					   SystemType type);

		//Removes the system of the specified type
		void removeSystem(SystemType type);

	private:

#ifdef NET_PHYSICS_CLIENT
		//Pointer to unreal engine world.
		UWorld* world;
#endif /* NET_PHYSICS_CLIENT */
		//"Data Indexers" for local and network data
		HandleManager handleManager;
		NetworkHandleManager networkHandleManager;
		//Game Object Manager
		GameObjectManager gameObjectManager;
		//Abstract base class containers for components and systems.
		XLib::Vector<ComponentManager> componentManagerContainer;
		XLib::Vector<System*> systemContainer;
	};
}

#endif /* REGISTER_H_INCLUDED */