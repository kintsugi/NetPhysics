#include "TimerSystem.h"
#include "XLib.h"

//Register includes
#include "Register.h"
#include "GameObject.h"

//For component function
#include "TimerComponent.h"

using namespace NetPhysics;

TimerSystem::TimerSystem() : System(BOTH), componentList(TIMER_COMPONENT) {}

void TimerSystem::update(Register &engineRegister, const double dt) {
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	XLib::Vector<GameObject*> gameObjects = gameObjectManager->getGameObjectsWithComponents(componentList);
	TimerComponent* timerComponent;
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		timerComponent = (*iter)->getComponent<TimerComponent>(*handleManager, TIMER_COMPONENT);
		if (timerComponent) {
			timerComponent->tick(dt);
		}
	}
}