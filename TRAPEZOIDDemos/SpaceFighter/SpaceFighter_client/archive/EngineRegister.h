#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "RakPeerInterface.h"
#include "HideWindowsPlatformTypes.h"

enum ManagerType {
	HANDLE_MANAGER,
	NETWORK_HANDLE_MANAGER,
	NETWORK_MANAGER,
	NUM_MANAGER_TYPES,
};

enum SystemType {
	CONNECTION_SYSTEM,
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
	TArray<void*> managerContainer;
	TArray<void*> systemContainer;
};

template <class T>
T* EngineRegister::getManager(ManagerType type) {
	return (T*)managerContainer[type];
}

template <class T>
T* EngineRegister::getSystem(SystemType type) {
	return (T*)systemContainer[type];
}
