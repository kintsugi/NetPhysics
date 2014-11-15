#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

#include "EngineRegister.h"
#ifdef SERVER
	#include "ServerSystem.h"
#endif /* SERVER */
#include "System.h"

void EngineRegister::init() {
#ifdef SERVER
	//Set max size for the system container
	systemContainer.resize(NUM_SYSTEM_TYPES);

	//initialize the component managers
	for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.push_back(ComponentManager((ComponentType)i));
	}

	//Init Server System
	initSystem(new ServerSystem(), SERVER_SYSTEM);
	ServerSystem* serverSystem = (ServerSystem*)getSystem(SERVER_SYSTEM);
	serverSystem->startServer(false);
	rakPeerInstance = serverSystem->getRakNetInstance();
#endif /* SERVER */
#ifdef CLIENT
	//initialize the component managers
	for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; i++) {
		componentManagerContainer.Add(ComponentManager((ComponentType)i));
	}
	systemContainer.InsertZeroed(0, NUM_SYSTEM_TYPES);
#endif CLIENT /* CLIENT */
}

void EngineRegister::update(double dt) {
#ifdef SERVER
	for (auto iter = componentManagerContainer.begin(); iter != componentManagerContainer.end(); iter++) {
		iter->update(handleManager);
	}
	for (auto iter = systemContainer.begin(); iter != systemContainer.end(); iter++) {
		if (*iter)
			(*iter)->update(this, dt);
	}
#endif/* SERVER */
#ifdef CLIENT
	for (auto iter = componentManagerContainer.CreateIterator(); iter; iter++) {
		iter->update(handleManager);
	}
	for (auto iter = systemContainer.CreateIterator(); iter; iter++) {
		if (iter->Get())
			(*iter)->update(this, dt);
	}
#endif /* CLIENT */
}

HandleManager* EngineRegister::getHandleManager() {
	return &handleManager;
}

NetworkHandleManager* EngineRegister::getNetworkHandleManager() {
	return &networkHandleManager;
}

#ifdef SERVER
GameObjectManager* EngineRegister::getGameObjectManager() {
	return &gameObjectManager;
}
#endif /* SERVER */
#ifdef CLIENT
void EngineRegister::setWorld(UWorld* world) {
	world = world;
}
UWorld* EngineRegister::getWorld() {
	return world;
}
#endif /* CLIENT */

RakNet::RakPeerInterface* EngineRegister::getRakPeerInstance() {
	return rakPeerInstance;
}

ComponentManager* EngineRegister::getComponentManager(ComponentType type) {
	return &componentManagerContainer[type];
}

System* EngineRegister::getSystem(SystemType type) {
#ifdef SERVER
	return systemContainer[type].get();
#endif /* SERVER */
#ifdef CLIENT
	return systemContainer[type].Get();
#endif /* CLIENT */
}

void EngineRegister::initSystem(System* newSystem, SystemType type) {
	systemContainer[type] = XLib::SharedPtr<System>(newSystem);
}

void EngineRegister::removeSystem(SystemType type) {
#ifdef SERVER
	systemContainer[type].reset();
#endif /* SERVER */
}