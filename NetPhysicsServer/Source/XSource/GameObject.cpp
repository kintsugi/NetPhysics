#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObject.h"
#include "HandleManager.h"
#include "Component.h"
#include "ComponentList.h"

using namespace NetPhysics;

GameObject::GameObject(HandleManager &handleManager) :
					   handle(handleManager.add(this,
												GAME_OBJECT)) {}

bool GameObject::addComponent(HandleManager &handleManager, const ComponentHandle componentHandle) {
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

void GameObject::removeComponent(HandleManager &handleManager,
								 const ComponentType type) {
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
	return got != NULL ? true : false;
#endif /* NET_PHYSICS_CLIENT */
}

bool GameObject::hasComponents(const ComponentList &componentList) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter = componentList.list.begin(); iter != componentList.list.end(); iter++) {
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = componentList.CreateIterator(); iter; iter++) {
#endif /* NET_PHYSICS_CLIENT */
		if (!hasComponent(iter->first))
			return false;
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
		for (auto iter = components.CreateIterator(); iter; ++iter) {
			Component* component = static_cast<Component*>(handleManager.get(iter.Value()));
#endif /* NET_PHYSICS_CLIENT */
		if (component)
			component->destroy(handleManager);
	}
	//remove self
	handleManager.remove(handle);
}

bool GameObject::addChild(Handle child) {
	if (!isChild(child)) {
#ifdef NET_PHYSICS_SERVER
		children.push_back(child);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		children.Add(child);
#endif /* NET_PHYSICS_CLIENT */
	}
	return false;
}

bool GameObject::removeChild(Handle child) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		if (child == *iter) {
			children.erase(iter);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = children.CreateIterator(); iter; iter++) {
		if (child == *iter) {
			children.RemoveAt(iter.GetIndex());
#endif /* NET_PHYSICS_CLIENT */
			return true;
		}
	}
	return false;
}

void GameObject::removeChildren() {
#ifdef NET_PHYSICS_SERVER
	children.clear();
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	children.Reset();
#endif /* NET_PHYSICS_CLIENT */

}

XLib::Vector<Handle> GameObject::getChildren() {
	return children;
}

bool GameObject::isChild(Handle child) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter = children.begin(); iter != children.end(); iter++) {
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = children.CreateIterator(); iter; iter++) {
#endif /* NET_PHYSICS_CLIENT */
		if (child == *iter) {
			return true;
		}
	}
	return false;
}

Handle GameObject::getHandle() const {
	return handle;
}

XLib::String GameObject::getTag() {
	return tag;
}
void GameObject::setTag(XLib::String newTag) {
	tag = newTag;
}