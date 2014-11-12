#ifndef TEST_ENGINE_REGISTER_H_INCLUDED
#define TEST_ENGINE_REGISTER_H_INCLUDED

#ifdef CLIENT
	#undef ENGINE_REGISTER_H	
	#pragma once
	#include "NetPhysics_client.h"
#endif /* CLIENT */

#ifdef CLIENT
#include "AllowWindowsPlatformTypes.h"
#endif /* CLIENT */
#include "RakPeerInterface.h"
#ifdef CLIENT
#include "HideWindowsPlatformTypes.h"
#endif /* CLIENT */

#include "XLib.h"
#include "HandleManager.h"
#ifdef SERVER
	#include "GameObjectManager.h"
#endif /* SERVER */
#include "NetworkHandleManager.h"
#include "ComponentManager.h"

enum ComponentType {
#ifdef SERVER
	CLIENT_COMPONENT,
	PHYSICS_COMPONENT,
	PLAYER_STATE_COMPONENT,
	TIMER_COMPONENT,
#endif /* SERVER */
	NETWORK_COMPONENT,
	NUM_COMPONENT_TYPES
};

enum SystemType {
#ifdef SERVER
	SERVER_SYSTEM,
	CLIENT_SYSTEM,
	PHYSICS_SYSTEM,
	PLAYER_INIT_SYSTEM,
#endif /* SERVER */
#ifdef CLIENT
	CONNECTION_SYSTEM,
#endif /* CLIENT */
	PACKET_HANDLER_SYSTEM,
	NETWORK_SYSTEM,
	NUM_SYSTEM_TYPES,
};

class System;

class EngineRegister {
public:
	void init();
	void update(double dt);

	HandleManager* getHandleManager();
	NetworkHandleManager* getNetworkHandleManager();
#ifdef SERVER
	GameObjectManager* getGameObjectManager();
#endif /* SERVER */
	RakNet::RakPeerInterface* getRakPeerInstance();

	ComponentManager* getComponentManager(ComponentType type);
	System* getSystem(SystemType type);

	void initSystem(System* newSystem, SystemType type);
	void removeSystem(SystemType type);


private:

	//Ptr to server instance of RakNet.
	RakNet::RakPeerInterface *rakPeerInstance;
	//"Data Indexers" for local and network data
	HandleManager handleManager;
	NetworkHandleManager networkHandleManager;

#ifdef SERVER
	//Game Object Manager
	GameObjectManager gameObjectManager;
#endif /* SERVER */

	//Abstract base class containers for components and systems.
	XLib::Vector<ComponentManager> componentManagerContainer;
	XLib::Vector<XLib::SharedPtr<System>> systemContainer;

};


#endif TEST_ENGINE_REGISTER_H_INCLUDED