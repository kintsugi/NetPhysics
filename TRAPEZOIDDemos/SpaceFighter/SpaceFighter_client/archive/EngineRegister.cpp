#include "SpaceFighter_client.h"
#include "engineregister.h"

EngineRegister::EngineRegister() {
	managerContainer.InsertUninitialized(0, NUM_MANAGER_TYPES);
	systemContainer.InsertUninitialized(0, NUM_SYSTEM_TYPES);
}

void EngineRegister::init(RakNet::RakPeerInterface* peer) {
	rakPeerInstance = peer;
}

void EngineRegister::addManager(void* manager, ManagerType type) {
	managerContainer[type] = manager;
}

void EngineRegister::addSystem(void* system, SystemType type) {
	systemContainer[type] = system;
}

RakNet::RakPeerInterface* EngineRegister::getRakPeerInstance() {
	return rakPeerInstance;
}