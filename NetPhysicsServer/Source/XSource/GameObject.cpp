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
#ifdef NET_PHYSICS_SERVER
		components.insert(std::make_pair(componentHandle.componentType, componentHandle));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		components.Add(componentHandle.componentType, componentHandle);
#endif /* NET_PHYSICS_CLIENT */
		Component* component = static_cast<Component*>(handleManager.get(componentHandle));
		component->setOwner(handle);
		return true;
	}
	return false;
}

//Returns a ComponentList object that contains the component ptrs
ComponentList GameObject::getComponents(HandleManager &handleManager) {
	ComponentList componentList;
#ifdef NET_PHYSICS_SERVER
	for (auto iter = components.begin(); iter != components.end(); iter++) {
		ComponentType componentType = iter->first;
		Component* component = reinterpret_cast<Component*>(handleManager.get(iter->second));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = components.CreateIterator(); iter; iter.operator++()) {
		ComponentType componentType = iter.Key();
		Component* component = reinterpret_cast<Component*>(handleManager.get(iter.Value()));
#endif /* NET_PHYSICS_CLIENT */
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
#ifdef NET_PHYSICS_SERVER
	auto got = components.find(type);
	if (got != components.end()) {
		Component* component = static_cast<Component*>(handleManager.get(got->second));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	ComponentHandle* got = components.Find(type);
	if (got) {
		Component* component = static_cast<Component*>(handleManager.get(*got));
#endif /* NET_PHYSICS_CLIENT */
		//If the component still exists in memory, call Component::destroy()
		if (component)
			component->destroy(handleManager);
		//Remove the component from the container.
#ifdef NET_PHYSICS_SERVER
		components.erase(got);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		components.Remove(type);
#endif /* NET_PHYSICS_CLIENT */
	}
}

bool GameObject::hasComponent(const ComponentType type) {
#ifdef NET_PHYSICS_SERVER
	auto got = components.find(type);
	return got != components.end() ? true : false;
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	ComponentHandle* got = components.Find(type);
	return got != nullptr ? true : false;
#endif /* NET_PHYSICS_CLIENT */
}

bool GameObject::hasComponents(ComponentList &componentList) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter=componentList.components.begin(); iter != componentList.components.end(); iter++)
	{
		if (!hasComponent(iter->first))
			return false;
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		for (auto iter = componentList.components.CreateIterator(); iter; iter.operator++()) {
		if (!hasComponent(iter.Key()))
			return false;
#endif /* NET_PHYSICS_CLIENT */
	}
	return true;
}

void GameObject::destroy(HandleManager &handleManager) {
	//Call Component::destroy for all components
#ifdef NET_PHYSICS_SERVER
	for (auto iter = components.begin(); iter != components.end(); iter++) {
		Component* component = static_cast<Component*>(handleManager.get(iter->second));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		for (auto iter = components.CreateIterator(); iter; iter.operator++()) {
			Component* component = static_cast<Component*>(handleManager.get(iter.Value()));
#endif /* NET_PHYSICS_CLIENT */
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