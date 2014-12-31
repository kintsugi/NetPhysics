#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
	#include "ConnectionSystem.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Register.h"
#ifdef NET_PHYSICS_SERVER
#include "ServerSystem.h"
#endif /* NET_PHYSICS_SERVER */
#include "System.h"
#include "GameObject.h"
#include "Component.h"

using namespace NetPhysics;

void Register::init() {
	//Set max size for the system container
	systemContainer.resize(NUM_SYSTEM_TYPES);

	//initialize the component managers
	for (uint32_t i = 0; i < NUM_COMPONENT_TYPES; i++)
		componentManagerContainer.push_back(ComponentManager((ComponentType)i));
}

void Register::update(const double dt) {
	//Update component managers and systems.
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

}

HandleManager* Register::getHandleManager() {
	return &handleManager;
}

NetworkHandleManager* Register::getNetworkHandleManager() {
	return &networkHandleManager;
}

//Returns the engine instance of the Replica Key Manager
ReplicaKeyManager* Register::getReplicaKeyManager() {
	return &replicaKeyManager;
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
	return systemContainer[type];
}

void Register::addSystem(System* newSystem, SystemType type) {
	newSystem->init();
	systemContainer[type] = newSystem;
}

void Register::removeSystem(SystemType type) {
	if (systemContainer[type]) {
		delete systemContainer[type];
		systemContainer[type] = nullptr;
	}
}

NetPhysics::HandleManager* hManagerMacro(NetPhysics::Register &reg) {
	return reg.getHandleManager();
}

NetPhysics::ReplicaKeyManager* rManagerMacro(NetPhysics::Register &reg) {
	return reg.getReplicaKeyManager();
}

NetPhysics::GameObjectManager* gObjManagerMacro(NetPhysics::Register &reg) {
	return reg.getGameObjectManager();
}

NetPhysics::GameObject* createGameObjectMacro(NetPhysics::Register &reg) {
	return reg.getGameObjectManager()->createGameObject(HANDLE_MANAGER, new GameObject());
}

NetPhysics::Component* createComponentMacro(
	NetPhysics::Register &reg,
	NetPhysics::Component* component)
{
	reg.getComponentManager(component->getType())->createComponent(HANDLE_MANAGER, component);
	return component;
}

NetPhysics::GameObjectList getGameObjectsWithMacro(
	NetPhysics::Register &reg,
	NetPhysics::ComponentList list)
{
	return reg.getGameObjectManager()->getGameObjectsWithComponents(list);
}