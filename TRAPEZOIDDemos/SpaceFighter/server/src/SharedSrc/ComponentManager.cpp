#ifdef CLIENT
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"

void ComponentManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}

Handle ComponentManager::createComponent(Component* component) {
	container.push_back(XLib::SharedPtr<Component>(component));
	return container.back()->getHandle();
}