#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"

using namespace NetPhysics;

ComponentManager::ComponentManager(const ComponentType type) : managerType(type) {}

void ComponentManager::update(HandleManager &handleManager) {
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
#endif  /* NET_PHYSICS_CLIENT */
}

ComponentHandle ComponentManager::createComponent(Component* component) {
#ifdef NET_PHYSICS_SERVER
	container.push_back(XLib::SharedPtr<Component>(component));
	return ComponentHandle(container.back()->getHandle(), managerType);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	container.Add(XLib::SharedPtr<Component>(component));
	return ComponentHandle(container.Last()->getHandle(), managerType);
#endif /* NET_PHYSICS_CLIENT */
}