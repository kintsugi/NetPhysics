#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObjectManager.h"
#include "GameObject.h"
#include "HandleManager.h"

using namespace NetPhysics;

void GameObjectManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle())) {
#ifdef NET_PHYSICS_SERVER
			iter = container.erase(iter);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			container.erase(iter);
			iter--;
#endif /* NET_PHYSICS_CLIENT */
		} else
			iter++;
	}
}

GameObject* GameObjectManager::createGameObject(GameObject* gameObject) {
	container.push_back(std::shared_ptr<GameObject>(gameObject));
	return &*container.back();
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