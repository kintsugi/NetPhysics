#ifndef TEST_ENGINE_REGISTER_H_INCLUDED
#define TEST_ENGINE_REGISTER_H_INCLUDED

#ifdef CLIENT
	#undef ENGINE_REGISTER_H	
	#pragma once
	#include "SpaceFighter_client.h"

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
#include "GameObjectManager.h"
#include "NetworkHandleManager.h"
#include "ComponentManager.h"

enum ComponentType {
#ifdef SERVER
	CLIENT_COMPONENT,
	PHYSICS_COMPONENT,
	PLAYER_STATE_COMPONENT,
	TIMER_COMPONENT,
#endif /* SERVER */
	NETWORK,
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
	NUM_SYSTEM_TYPES,
};

class System;

class TestEngineRegister {
public:
	void init();

	HandleManager* getHandleManager();
	NetworkHandleManager* getNetworkHandleManager();
	GameObjectManager* getGameObjectManager();
	
	ComponentManager* getComponentManager(ComponentType type);

	void initSystem(System* newSystem, SystemType type);
	void removeSystem(SystemType type);

	template <class T>
	T* getSystem(SystemType type);


private:

	//Ptr to server instance of RakNet.
	RakNet::RakPeerInterface *RakPeerInstance;
	//"Data Indexers" for local and network data
	HandleManager handleManager;
	NetworkHandleManager networkHandleManager;

	//Game Object Manager
	GameObjectManager gameObjectManager;

	//Abstract base class containers for components and systems.
	XLib::Vector<ComponentManager> componentManagerContainer;
	XLib::Vector<XLib::SharedPtr<System>> systemContainer;

};

template <class T>
T* TestEngineRegister::getSystem(SystemType type) {
	return (T*)systemContainer[type];
}


#endif TEST_ENGINE_REGISTER_H_INCLUDED