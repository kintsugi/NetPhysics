#include "gameobjectmanager.h"
#include "handlemanager.h"

void GameObjectManager::update(HandleManager* handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager->get(iter->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

GameObject* GameObjectManager::createGameObject(HandleManager* handleManager) {
	container.push_back(GameObject());
	container.back().handle = handleManager->add(&container.back(), 0);
	return &container.back();
}