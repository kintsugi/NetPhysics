#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObject.h"
#include "HandleManager.h"
#include "Component.h"
#include "Logger.h"

using namespace NetPhysics;

bool GameObject::addComponent(
	HandleManager &handleManager,
	const ComponentHandle componentHandle)
{
	//Game object cannot have two components of the same type.
	if (componentHandle.type == COMPONENT && !hasComponent(componentHandle.componentType)) {
		//Insert into map and set the components owner.
		components.insert(std::make_pair(componentHandle.componentType, componentHandle));
		Component* component = static_cast<Component*>(handleManager.get(componentHandle));
		component->setOwner(handle);
		return true;
	}
	DEBUG_LOG(ERROR_MSG, "attempting to add a component which handle is not a valid type");
	return false;
}

bool GameObject::addComponent(Component* component){
	//Game object cannot have two components of the same type.
	ComponentHandle componentHandle = component->getComponentHandle();
	if (componentHandle.type == COMPONENT && !hasComponent(componentHandle.componentType)) {
		//Insert into map and set the components owner.
		components.insert(std::make_pair(componentHandle.componentType, componentHandle));
		component->setOwner(handle);
		return true;
	}
	DEBUG_LOG(ERROR_MSG, "attempting to add a component which handle is not a valid type");
	return false;
}

Component* GameObject::getComponent(
	HandleManager &handleManager,
	const ComponentType type)
{
	return getComponent<Component>(handleManager, type);
}

ComponentList GameObject::getComponents(HandleManager &handleManager) {
	ComponentList componentList;
	for (auto iter = components.begin(); iter != components.end(); ++iter) {
		ComponentType componentType = iter->first;
		Component* component = reinterpret_cast<Component*>(handleManager.get(iter->second));
		if (component)
			componentList.add(componentType, component);
	}
	return componentList;
}

void GameObject::getComponents(
	HandleManager &handleManager,
	ComponentList &out)
{
	//Use key value in out to look for components in the game object.
	for (auto iter = out.components.begin(); iter != out.components.end(); ++iter) {
		auto got = components.find(iter->first);
		if (got != components.end())
			iter->second = reinterpret_cast<Component*>(handleManager.get(got->second));
	}
}

void GameObject::removeComponent(
	HandleManager &handleManager,
	const ComponentType type)
{
	//Make sure the component of that type exists in this GameObject
	auto got = components.find(type);
	if (got != components.end()) {
		Component* component = static_cast<Component*>(handleManager.get(got->second));
		//If the component still exists in memory, call Component::destroy()
		if (component)
			component->destroy(handleManager);
		//Remove the component from the container.
		components.erase(type);
	}
}

bool GameObject::hasComponent(const ComponentType type) {
	auto got = components.find(type);
	return got != components.end() ? true : false;
}

bool GameObject::hasComponents(ComponentList &componentList) {
	for (auto iter = componentList.components.begin(); iter != componentList.components.end(); ++iter) {
		if (!hasComponent(iter->first))
			return false;
	}
	return true;
}

void GameObject::destroy(HandleManager &handleManager) {
	//Call Component::destroy for all components
	for (auto iter = components.begin(); iter != components.end(); ++iter) {
		Component* component = static_cast<Component*>(handleManager.get(iter->second));
		if (component)
			component->destroy(handleManager);
	}
	//remove self
	handleManager.remove(handle);
}

Handle GameObject::getHandle() const {
	return handle;
}

std::string GameObject::getTag() {
	return tag;
}

//Family* GameObject::getFamily() {
//	return &family;
//}

void GameObject::setTag(std::string newTag) {
	tag = newTag;
}