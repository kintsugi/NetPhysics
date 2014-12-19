#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"

using namespace NetPhysics;

ComponentManager::ComponentManager(const ComponentType type)
	: managerType(type)
{}

void ComponentManager::update(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager.get((*iter)->getHandle())) {
			container.erase(iter);
			iter--;
		}
		else
			iter++;
	}
}

ComponentHandle ComponentManager::createComponent(Component* component) {
	if (component->getComponentHandle().componentType == managerType) {
		container.push_back(XLib::SharedPtr<Component>(component));
		return ComponentHandle(container.back()->getHandle(), managerType);
	}
	//TODO: debug log this exception
	return ComponentHandle(Handle(), NULL_COMPONENT);
}