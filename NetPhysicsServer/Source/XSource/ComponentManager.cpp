#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"
#include "Logger.h"
#include <string>

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

ComponentHandle ComponentManager::createComponent(
	HandleManager &handleManager, 
	Component* component)
{
	if (component->getType() == managerType) {
		ComponentHandle compHandle(
			handleManager.add(component, COMPONENT),
			managerType);
		component->handle = compHandle;
		container.push_back(std::shared_ptr<Component>(component));
		return compHandle;
	}
	//TODO: debug log this exception
	DEBUG_LOG(ERROR_MSG,
		"attempted to create component type enum #" +
		std::to_string(component->getComponentHandle().componentType) +
		" with invalid manager type enum #" + std::to_string(managerType));
	return ComponentHandle(Handle(), NULL_COMPONENT);
}