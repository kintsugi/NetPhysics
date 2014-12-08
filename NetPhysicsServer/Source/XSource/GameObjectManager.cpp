#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObjectManager.h"
#include "GameObject.h"
#include "HandleManager.h"

using namespace NetPhysics;

void GameObjectManager::update(HandleManager &handleManager) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = container.CreateIterator(); iter;) {
		if (!handleManager.get((*iter)->getHandle())) {
			container.RemoveAt(iter.GetIndex());
			iter--;
		} else
			iter++;
	}
#endif /* NET_PHYSICS_CLIENT */
}

GameObject* GameObjectManager::createGameObject(GameObject* gameObject) {
#ifdef NET_PHYSICS_SERVER
	container.push_back(XLib::SharedPtr<GameObject>(gameObject));
	return container.back().get();
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	container.Add(XLib::SharedPtr<GameObject>(gameObject));
	return container.Last().Get();
#endif /* NET_PHYSICS_CLIENT */
}

XLib::Vector<GameObject*> GameObjectManager::getGameObjectsWithComponents(
	const ComponentList &componentList)
{
	XLib::Vector<GameObject*> ret;
#ifdef NET_PHYSICS_SERVER
	for (auto iter = container.begin(); iter != container.end();iter++) {
		if ((*iter)->hasComponents(componentList))
			ret.push_back(iter->get());
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = container.CreateIterator(); iter; iter++) {
		if ((*iter)->hasComponents(componentList))
			ret.Add(iter->Get());
	}
#endif /* NET_PHYSICS_CLIENT */
	return ret;
}