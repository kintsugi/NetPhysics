#include "SpaceFighter_client.h"
#include "gameobjectmanager.h"
#include "handlemanager.h"

void GameObjectManager::update(HandleManager &handleManager) {
	for (auto iter = container.CreateIterator(); iter;) {
		if (!handleManager.get(iter->getHandle())) {
			container.RemoveAt(iter.GetIndex());
			iter--;
		} else
			iter++;
	}
}

GameObject* GameObjectManager::createGameObject(HandleManager &handleManager) {
	container.Add(GameObject(handleManager));
	return &container.Last();
}

TArray<Handle> GameObjectManager::getGameObjects(const GameObjectFilter filter) {
	TArray<Handle> ret;
	for (auto iter = container.CreateIterator(); iter; iter++) {
		if (iter->hasComponents(filter))
			ret.Add(iter->getHandle());
	}
	return ret;
}