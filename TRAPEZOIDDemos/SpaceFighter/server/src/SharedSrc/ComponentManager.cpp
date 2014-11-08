#ifdef CLIENT
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"

void ComponentManager::update(HandleManager &handleManager) {
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
#endif  /* CLIENT */
}

Handle ComponentManager::createComponent(Component* component) {
#ifdef SERVER
	container.push_back(XLib::SharedPtr<Component>(component));
	return container.back()->getHandle();
#endif /* SERVER */
#ifdef CLIENT
	container.Add(XLib::SharedPtr<Component>(component));
	return container.Last()->getHandle();
#endif
}