#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObjectManager.h"
#include "GameObject.h"
#include "HandleManager.h"

using namespace NetPhysics;

void GameObjectManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

GameObject* GameObjectManager::createGameObject(
	HandleManager &handleManager, 
	GameObject* gameObject)
{
	Handle handle = handleManager.add(gameObject, GAME_OBJECT);
	gameObject->handle = handle;
	container.push_back(std::shared_ptr<GameObject>(gameObject));
	return container.back().get();
}

GameObjectList GameObjectManager::getGameObjectsWithComponents(
	ComponentList &componentList)
{
	std::vector<GameObject*> ret;
	for (auto iter = container.begin(); iter != container.end();iter++) {
		if ((*iter)->hasComponents(componentList))
			ret.push_back(iter->get());
	}
	return GameObjectList(ret);
}