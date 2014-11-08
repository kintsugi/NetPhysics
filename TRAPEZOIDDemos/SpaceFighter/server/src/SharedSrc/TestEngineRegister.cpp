#ifdef CLIENT
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "TestEngineRegister.h"
#include "System.h"

void TestEngineRegister::init() {
	componentManagerContainer.resize(NUM_COMPONENT_TYPES);
	systemContainer.resize(NUM_SYSTEM_TYPES);

}

HandleManager* TestEngineRegister::getHandleManager() {
	return &handleManager;
}

NetworkHandleManager* TestEngineRegister::getNetworkHandleManager() {
	return &networkHandleManager;
}

GameObjectManager* TestEngineRegister::getGameObjectManager() {
	return &gameObjectManager;
}

ComponentManager* TestEngineRegister::getComponentManager(ComponentType type) {
	return &componentManagerContainer[type];
}

void TestEngineRegister::initSystem(System* newSystem, SystemType type) {
	systemContainer[type] = XLib::SharedPtr<System>(newSystem);
}

void TestEngineRegister::removeSystem(SystemType type) {
	systemContainer[type].reset();
}