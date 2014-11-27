#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
	#include "ConnectionSystem.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Register.h"
#ifdef NET_PHYSICS_SERVER
#include "ServerSystem.h"
#endif /* NET_PHYSICS_SERVER */
#include "System.h"

using namespace NetPhysics;

void Register::init() {
#ifdef NET_PHYSICS_SERVER
	//Set max size for the system container
	systemContainer.resize(NUM_SYSTEM_TYPES);

	//initialize the component managers
	for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.push_back(ComponentManager((ComponentType)i));
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	//initialize the component managers
	for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.Add(ComponentManager((ComponentType)i));
	}
	systemContainer.InsertZeroed(0, NUM_SYSTEM_TYPES);
#endif NET_PHYSICS_CLIENT /* NET_PHYSICS_CLIENT */
}

void Register::update(const double dt) {
	//Update component managers and systems.
#ifdef NET_PHYSICS_SERVER
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
					(*iter)->update(*this);
					break;
				case BOTH:
					(*iter)->update(*this, dt);
					break;
			}
		}
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
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
				(*iter)->update(*this);
				break;
			case BOTH:
				(*iter)->update(*this, dt);
				break;
			}
		}
	}
#endif /* NET_PHYSICS_CLIENT */
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

#ifdef NET_PHYSICS_CLIENT
void Register::setWorld(UWorld* world) {
	world = world;
}
UWorld* Register::getWorld() {
	return world;
}
#endif /* NET_PHYSICS_CLIENT */

RakNet::RakPeerInterface* Register::getRakPeerInstance() {
#ifdef NET_PHYSICS_SERVER
	ServerSystem* serverSystem = (ServerSystem*)getSystem(SERVER_SYSTEM);
	return serverSystem->getRakPeerInstance();
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	ConnectionSystem* connectionSystem = (ConnectionSystem*)getSystem(CONNECTION_SYSTEM);
	return connectionSystem->getRakPeerInstance();
#endif /* NET_PHYSICS_CLIENT */
}

ComponentManager* Register::getComponentManager(ComponentType type) {
	return &componentManagerContainer[type];
}

System* Register::getSystem(SystemType type) {
#ifdef NET_PHYSICS_SERVER
	return systemContainer[type];
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	return systemContainer[type];
#endif /* NET_PHYSICS_CLIENT */
}

void Register::addSystem(System* newSystem,
						 SystemType type) {
	newSystem->init();
	systemContainer[type] = newSystem;
}

void Register::removeSystem(SystemType type) {
#ifdef NET_PHYSICS_SERVER
	if (systemContainer[type]) {
		delete systemContainer[type];
		systemContainer[type] = NULL;
	}
#endif /* NET_PHYSICS_SERVER */
}