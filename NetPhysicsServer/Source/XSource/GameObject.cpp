#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif /* CLIENT */
#include "GameObject.h"
#include "HandleManager.h"
#include "Component.h"

GameObject::GameObject(HandleManager &handleManager) : 
					   handle(handleManager.add(this, GAME_OBJECT)) {}

bool GameObject::addComponent(HandleManager &handleManager, const ComponentHandle componentHandle) {
	//Game object cannot have two components of the same type.
	if (componentHandle.type == COMPONENT && !hasComponent(componentHandle.componentType)) {
		//Insert into map and set the components owner.
#ifdef SERVER
		components.insert(std::make_pair(componentHandle.componentType, componentHandle));
#endif /* SERVER */
#ifdef CLIENT
		components.Add(componentHandle.componentType, componentHandle);
#endif
		Component* component = (Component*)handleManager.get(componentHandle);
		component->setOwner(handle);
		return true;
	}
	return false;
}

void GameObject::removeComponent(HandleManager &handleManager,
								 const ComponentType type) {
	//Make sure the component of that type exists in this GameObject
#ifdef SERVER
	auto got = components.find(type);
	if (got != components.end()) {
		Component* component = static_cast<Component*>(handleManager.get(got->second));
#endif /* SERVER */
#ifdef CLIENT
	ComponentHandle* got = components.Find(type);
	if (got) {
		Component* component = static_cast<Component*>(handleManager.get(*got));
#endif /* CLIENT */
		//If the component still exists in memory, call Component::destroy()
		if (component)
			component->destroy(handleManager);
		//Remove the component from the container.
#ifdef SERVER
		components.erase(got);
#endif /* SERVER */
#ifdef CLIENT
		components.Remove(type);
#endif /* CLIENT */
	}
}

bool GameObject::hasComponent(const ComponentType type) {
#ifdef SERVER
	auto got = components.find(type);
	return got != components.end() ? true : false;
#endif /* SERVER */
#ifdef CLIENT
	ComponentHandle* got = components.Find(type);
	return got != NULL ? true : false;
#endif /* CLIENT */
}

bool GameObject::hasComponents(const GameObjectFilter filter) {
	XLib::Vector<ComponentType> filterList = filter.getFilterList();
#ifdef SERVER
	for (auto iter = filterList.begin(); iter != filterList.end(); iter++) {
#endif /* SERVER */
#ifdef CLIENT
		for (auto iter = filterList.CreateIterator(); iter; iter++) {
#endif /* CLIENT */
		if (!hasComponent(*iter))
			return false;
	}
	return true;
}

void GameObject::destroy(HandleManager &handleManager) {
	//Call Component::destroy for all components
#ifdef SERVER
	for (auto iter = components.begin(); iter != components.end(); iter++) {
		Component* component = static_cast<Component*>(handleManager.get(iter->second));
#endif /* SERVER */
#ifdef CLIENT
		for (auto iter = components.CreateIterator(); iter; ++iter) {
			Component* component = static_cast<Component*>(handleManager.get(iter.Value()));
#endif /* CLIENT */
		if (component)
			component->destroy(handleManager);
	}
	//remove self
	handleManager.remove(handle);
}

bool GameObject::addChild(Handle child) {
	if (!isChild(child)) {
#ifdef SERVER
		children.push_back(child);
#endif /* SERVER */
#ifdef CLIENT
		children.Add(child);
#endif /* CLIENT */
	}
	return false;
}

bool GameObject::removeChild(Handle child) {
#ifdef SERVER
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		if (child == *iter) {
			children.erase(iter);
#endif /* SERVER */
#ifdef CLIENT
	for (auto iter = children.CreateIterator(); iter; iter++) {
		if (child == *iter) {
			children.RemoveAt(iter.GetIndex());
#endif /* CLIENT */
			return true;
		}
	}
	return false;
}

void GameObject::removeChildren() {
#ifdef SERVER
	children.clear();
#endif /* SERVER */
#ifdef CLIENT
	children.Reset();
#endif /* CLIENT */

}

XLib::Vector<Handle> GameObject::getChildren() {
	return children;
}

bool GameObject::isChild(Handle child) {
#ifdef SERVER
	for (auto iter = children.begin(); iter != children.end(); iter++) {
#endif /* SERVER */
#ifdef CLIENT
	for (auto iter = children.CreateIterator(); iter; iter++) {
#endif /* CLIENT */
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