#include "TimerSystem.h"


//Register includes
#include "Register.h"
#include "GameObject.h"

//For component function
#include "TimerComponent.h"

using namespace NetPhysics;

TimerSystem::TimerSystem() : System(BOTH), componentList(TIMER_COMPONENT) {}

void TimerSystem::update(Register &reg, const double dt) {
	HandleManager* handleManager = reg.getHandleManager();
	GameObjectManager* gameObjectManager = reg.getGameObjectManager();

	GameObjectList gameObjectList = gameObjectManager->getGameObjectsWithComponents(componentList);
	GameObject* gameObject;
	TimerComponent* timerComponent;
	for (gameObject = gameObjectList.next(); gameObject; gameObject = gameObjectList.next()) {
		timerComponent = gameObject->getComponent<TimerComponent>(*handleManager, TIMER_COMPONENT);
		if (timerComponent) {
			timerComponent->tick(dt);
		}
	}
}