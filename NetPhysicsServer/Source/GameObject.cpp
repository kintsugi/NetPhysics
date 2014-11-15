#include "GameObject.h"
#include "HandleManager.h"
#include "Component.h"

GameObject::GameObject(HandleManager &handleManager) : 
	messenger(handleManager), 
	handle(handleManager.add(this, GAME_OBJECT)) {}

bool GameObject::addComponent(HandleManager &handleManager, const ComponentHandle componentHandle) {
	//Handle::subType is used to describe the type of component for game objects
	//Game object cannot have two components of the same type.
	if (componentHandle.type == COMPONENT && !hasComponent(componentHandle.componentType)) {
		//Insert into map and set the components owner.
		components.insert(std::make_pair(componentHandle.componentType, componentHandle));
		Component* component = (Component*)handleManager.get(componentHandle);
		component->setOwner(handle);
		return true;
	}
	return false;
}

void GameObject::removeComponent(HandleManager &handleManager, ComponentType type) {
	//Make sure the component of that type exists in this GameObject
	auto got = components.find(type);
	if (got != components.end()) {
		//If the component still exists in memory, call Component::destroy()
		Component* component = (Component*)handleManager.get(got->second);
		if (component)
			component->destroy(handleManager);
		//Remove the component from the container.
		components.erase(got);
	}
}

bool GameObject::hasComponent(ComponentType type) {
	auto got = components.find(type);
	return got != components.end() ? true : false;
}

bool GameObject::hasComponents(GameObjectFilter filter) {
	XLib::Vector<ComponentType> filterList = filter.getFilterList();
	for (auto iter = filterList.begin(); iter != filterList.end(); iter++) {
		if (!hasComponent(*iter))
			return false;
	}
	return true;
}

void GameObject::destroy(HandleManager &handleManager) {
	//Call Component::destroy for all components
	for (auto iter = components.begin(); iter != components.end(); iter++) {
		Component* component = (Component*)handleManager.get(iter->second);
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
void GameObject::setTag(std::string newTag) {
	tag = newTag;
}

Messenger* GameObject::getMessenger() {
	return &messenger;
}