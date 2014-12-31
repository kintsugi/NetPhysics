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

#include "HandleManager.h"
#include "NetworkHandleManager.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "ComponentType.h"
#include "SystemType.h"
#include "ReplicaKeyManager.h"


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

		//Returns the engine instance of the Replica Key Manager
		ReplicaKeyManager* getReplicaKeyManager();

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
		ReplicaKeyManager replicaKeyManager;
		//Game Object Manager
		GameObjectManager gameObjectManager;
		//Abstract base class containers for components and systems.
		std::vector<ComponentManager> componentManagerContainer;
		std::vector<System*> systemContainer;
	};
}

NetPhysics::HandleManager* hManagerMacro(NetPhysics::Register &reg);
#define HANDLE_MANAGER *hManagerMacro(reg)

NetPhysics::ReplicaKeyManager* rManagerMacro(NetPhysics::Register &reg);
#define REPLICA_KEY_MANAGER *rManagerMacro(reg)

NetPhysics::GameObjectManager* gObjManagerMacro(NetPhysics::Register &reg);
#define GAME_OBJECT_MANAGER gObjManagerMacro(reg)

RakNet::RakPeerInterface* rakPeerInterfaceMacro(NetPhysics::Register &reg);
#define RAK_PEER_INTERFACE rakPeerInterfaceMacro(reg)

NetPhysics::GameObject* createGameObjectMacro(NetPhysics::Register &reg);
#define NEW_GAME_OBJECT createGameObjectMacro(reg)

NetPhysics::Component* createComponentMacro(
	NetPhysics::Register &reg,
	NetPhysics::Component* component);
#define NEW_COMPONENT(component) createComponentMacro(reg, component)

NetPhysics::GameObjectList getGameObjectsWithMacro(
	NetPhysics::Register &reg, 
	NetPhysics::ComponentList list);
#define GET_GAME_OBJECTS_WITH(list) getGameObjectsWithMacro(reg, list)

#endif /* REGISTER_H_INCLUDED */