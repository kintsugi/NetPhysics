#include "physicsmanager.h"
#include "physicscomponent.h"
#include "bulletphysicsobject.h"

void PhysicsManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get(iter->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle PhysicsManager::createComponent(HandleManager &handleManager, BulletPhysicsObject& obj) {
	container.push_back(PhysicsComponent(handleManager, obj));
	return container.back().getHandle();
}