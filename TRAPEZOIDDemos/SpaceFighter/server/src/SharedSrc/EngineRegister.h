#ifndef ENGINE_REGISTER_H
#define ENGINE_REGISTER_H

#ifdef CLIENT
	#undef ENGINE_REGISTER_H	
	#pragma once
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "XLib.h"
#include "RakPeerInterface.h"

enum ManagerType {
#ifdef SERVER
	GAME_OBJECT_MANAGER,
	PHYSICS_MANAGER,
	CLIENT_MANAGER,
	PLAYER_STATE_MANAGER,
	TIMER_MANAGER,
#endif /* SERVER */
	HANDLE_MANAGER,
	NETWORK_HANDLE_MANAGER,
	NETWORK_MANAGER,
	NUM_MANAGER_TYPES,
};

enum SystemType {
#ifdef SERVER
	SERVER_SYSTEM,
	PHYSICS_SYSTEM,
	PLAYER_INIT_SYSTEM,
	CLIENT_SYSTEM,
#endif /* SERVER */
	NETWORK_SYSTEM,
	PACKET_HANDLER_SYSTEM,
	NUM_SYSTEM_TYPES,
};

class EngineRegister {
public:

	EngineRegister();

	void init(RakNet::RakPeerInterface* peer);

	void addManager(void* manager, ManagerType type);
	void addSystem(void* system, SystemType type);

	template <class T>
	T* getManager(ManagerType type);

	template <class T>
	T* getSystem(SystemType type);

	RakNet::RakPeerInterface* getRakPeerInstance();

private:
	RakNet::RakPeerInterface* rakPeerInstance;
	XLib::Vector<void*> managerContainer;
	XLib::Vector<void*> systemContainer;
};

template <class T>
T* EngineRegister::getManager(ManagerType type) {
	return (T*)managerContainer[type];
}

template <class T>
T* EngineRegister::getSystem(SystemType type) {
	return (T*)systemContainer[type];
}

#endif /* ENGINE_REGISTER_H */