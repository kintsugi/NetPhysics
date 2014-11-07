#ifdef CLIENT
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "engineregister.h"

EngineRegister::EngineRegister() {
#ifdef SERVER

	managerContainer.resize(NUM_MANAGER_TYPES);
	systemContainer.resize(NUM_SYSTEM_TYPES);

#endif /* SERVER */
#ifdef CLIENT

	managerContainer.InsertZeroed(0, NUM_MANAGER_TYPES);
	systemContainer.InsertZeroed(0, NUM_SYSTEM_TYPES);

#endif /* CLIENT */
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