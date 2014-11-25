#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif /* CLIENT */
#include "GameObjectManager.h"
#include "GameObject.h"
#include "HandleManager.h"

void GameObjectManager::update(HandleManager &handleManager) {
#ifdef SERVER
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
#endif /* SERVER */
#ifdef CLIENT
	for (auto iter = container.CreateIterator(); iter;) {
		if (!handleManager.get((*iter)->getHandle())) {
			container.RemoveAt(iter.GetIndex());
			iter--;
		} else
			iter++;
	}
#endif /* CLIENT */
}

GameObject* GameObjectManager::createGameObject(GameObject* gameObject) {
#ifdef SERVER
	container.push_back(XLib::SharedPtr<GameObject>(gameObject));
	return container.back().get();
#endif /* SERVER */
#ifdef CLIENT
	container.Add(XLib::SharedPtr<GameObject>(gameObject));
	return container.Last().Get();
#endif /* CLIENT */
}

XLib::Vector<GameObject*> GameObjectManager::getGameObjects(const GameObjectFilter filter) {
	XLib::Vector<GameObject*> ret;
#ifdef SERVER
	for (auto iter = container.begin(); iter != container.end();iter++) {
		if ((*iter)->hasComponents(filter))
			ret.push_back(iter->get());
	}
#endif /* SERVER */
#ifdef CLIENT
	for (auto iter = container.CreateIterator(); iter; iter++) {
		if ((*iter)->hasComponents(filter))
			ret.Add(iter->Get());
	}
#endif /* CLIENT */
	return ret;
}