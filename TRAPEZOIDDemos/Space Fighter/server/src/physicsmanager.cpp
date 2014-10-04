#include "physicsmanager.h"
#include "physicscomponent.h"
#include "bulletphysicsobject.h"

void PhysicsManager::update(HandleManager* handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager->get(iter->get()->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle PhysicsManager::createComponent(HandleManager* handleManager, BulletPhysicsObject& obj) {
	std::unique_ptr<PhysicsComponent> newComponent(new PhysicsComponent(obj));
	container.push_back(std::move(newComponent));
	return handleManager->add(container.back().get(), PHYSICS);
}