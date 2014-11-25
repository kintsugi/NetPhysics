#ifdef CLIENT
	#include "NetPhysicsClient.h"
	#include "ConnectionSystem.h"
#endif /* CLIENT */

#include "Register.h"
#include "System.h"

#ifdef SERVER
#include "ServerSystem.h"
#endif /* SERVER */

void Register::init() {
#ifdef SERVER
	//Set max size for the system container
	systemContainer.resize(NUM_SYSTEM_TYPES);

	//initialize the component managers
	for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.push_back(ComponentManager((ComponentType)i));
	}
#endif /* SERVER */
#ifdef CLIENT
	//initialize the component managers
	for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.Add(ComponentManager((ComponentType)i));
	}
	systemContainer.InsertZeroed(0, NUM_SYSTEM_TYPES);
#endif CLIENT /* CLIENT */
}

void Register::update(const double dt) {
#ifdef SERVER
	for (auto iter = componentManagerContainer.begin(); iter != componentManagerContainer.end(); iter++) {
		iter->update(handleManager);
	}

	for (auto iter = systemContainer.begin(); iter != systemContainer.end(); iter++) {
		if (*iter) {
			switch ((*iter)->mode) {
				case NO_PARAMETERS:
					(*iter)->update();
					break;
				case DELTA_TIME:
					(*iter)->update(dt);
					break;
				case REGISTER:
					(*iter)->update(this);
					break;
				case BOTH:
					(*iter)->update(this, dt);
					break;
			}
		}
	}
#endif/* SERVER */
#ifdef CLIENT
	for (auto iter = componentManagerContainer.CreateIterator(); iter; iter++) {
		iter->update(handleManager);
	}

	for (auto iter = systemContainer.CreateIterator(); iter; iter++) {
		if (*iter) {
			switch ((*iter)->mode) {
			case NO_PARAMETERS:
				(*iter)->update();
				break;
			case DELTA_TIME:
				(*iter)->update(dt);
				break;
			case REGISTER:
				(*iter)->update(this);
				break;
			case BOTH:
				(*iter)->update(this, dt);
				break;
			}
		}
	}
#endif /* CLIENT */
}

HandleManager* Register::getHandleManager() {
	return &handleManager;
}

NetworkHandleManager* Register::getNetworkHandleManager() {
	return &networkHandleManager;
}


GameObjectManager* Register::getGameObjectManager() {
	return &gameObjectManager;
}

#ifdef CLIENT
void Register::setWorld(UWorld* world) {
	world = world;
}
UWorld* Register::getWorld() {
	return world;
}
#endif /* CLIENT */

RakNet::RakPeerInterface* Register::getRakPeerInstance() {
#ifdef SERVER
	ServerSystem* serverSystem = (ServerSystem*)getSystem(SERVER_SYSTEM);
	return serverSystem->getRakPeerInstance();
#endif /* SERVER */
#ifdef CLIENT
	ConnectionSystem* connectionSystem = (ConnectionSystem*)getSystem(CONNECTION_SYSTEM);
	return connectionSystem->getRakPeerInstance();
#endif /* CLIENT */
}

ComponentManager* Register::getComponentManager(ComponentType type) {
	return &componentManagerContainer[type];
}

System* Register::getSystem(SystemType type) {
#ifdef SERVER
	return systemContainer[type];
#endif /* SERVER */
#ifdef CLIENT
	return systemContainer[type];
#endif /* CLIENT */
}

void Register::addSystem(System* newSystem,
						 SystemType type) {
	newSystem->init();
	systemContainer[type] = newSystem;
}

void Register::removeSystem(SystemType type) {
#ifdef SERVER
	if (systemContainer[type]) {
		delete systemContainer[type];
		systemContainer[type] = NULL;
	}
#endif /* SERVER */
}