#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObject.h"
#include "HandleManager.h"
#include "Component.h"

using namespace NetPhysics;

GameObject::GameObject(HandleManager &handleManager)
	: handle(handleManager.add(this, GAME_OBJECT))
	, family(handle)
{}

bool GameObject::addComponent(
	HandleManager &handleManager,
	const ComponentHandle componentHandle)
{
	//Game object cannot have two components of the same type.
	if (componentHandle.type == COMPONENT && !hasComponent(componentHandle.componentType)) {
		//Insert into map and set the components owner.
		components.insert(componentHandle.componentType, componentHandle);
		Component* component = static_cast<Component*>(handleManager.get(componentHandle));
		component->setOwner(handle);
		return true;
	}
	return false;
}

//Returns a ComponentList object that contains the component ptrs
ComponentList GameObject::getComponents(HandleManager &handleManager) {
	ComponentList componentList;
	for (auto iter = components.begin(); iter != components.end(); ++iter) {
		ComponentType componentType = components.first(iter);
		Component* component = reinterpret_cast<Component*>(handleManager.get(components.second(iter)));
		if (component)
			componentList.add(componentType, component);
	}
	return componentList;
}


void GameObject::removeComponent(
	HandleManager &handleManager,
	const ComponentType type)
{
	//Make sure the component of that type exists in this GameObject
	ComponentHandle* got = components.find(type);
	if (got) {
		Component* component = static_cast<Component*>(handleManager.get(*got));
		//If the component still exists in memory, call Component::destroy()
		if (component)
			component->destroy(handleManager);
		//Remove the component from the container.
		components.erase(type);
	}
}

bool GameObject::hasComponent(const ComponentType type) {

	ComponentHandle* got = components.find(type);
	return got != nullptr ? true : false;
}

bool GameObject::hasComponents(ComponentList &componentList) {
	for (auto iter = componentList.components.begin(); iter != componentList.components.end(); ++iter) {
		if (!hasComponent(componentList.components.first(iter)))
			return false;
	}
	return true;
}

void GameObject::destroy(HandleManager &handleManager) {
	//Call Component::destroy for all components
	for (auto iter = components.begin(); iter != components.end(); ++iter) {
		Component* component = static_cast<Component*>(handleManager.get(components.second(iter)));
		if (component)
			component->destroy(handleManager);
	}
	//remove self
	handleManager.remove(handle);
}

Handle GameObject::getHandle() const {
	return handle;
}

XLib::String GameObject::getTag() {
	return tag;
}

Family* GameObject::getFamily() {
	return &family;
}

void GameObject::setTag(XLib::String newTag) {
	tag = newTag;
}