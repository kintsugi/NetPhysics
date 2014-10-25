#include "gameobjectmanager.h"
#include "handlemanager.h"

void GameObjectManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get(iter->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

GameObject* GameObjectManager::createGameObject(HandleManager &handleManager) {
	container.push_back(GameObject(handleManager));
	return &container.back();
}

std::vector<Handle> GameObjectManager::getGameObjects(const GameObjectFilter filter) {
	std::vector<Handle> ret;
	for (auto iter = container.begin(); iter != container.end();iter++) {
		if (iter->hasComponents(filter))
			ret.push_back(iter->getHandle());
	}
	return ret;
}