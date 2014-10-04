#include "gameobject.h"
#include "handlemanager.h"

GameObject::GameObject() {
	//Initialize the components to have a component handle for each kind of component
	for (uint32 i = 0; i < ComponentType::NUMBER_OF_COMPONENT_TYPES; i++)
		components.insert(std::make_pair((ComponentType)i, ComponentTypeHandle()));
}

bool GameObject::addComponent(const Handle handle) {
	auto got = components.find((ComponentType)handle.type);
	if (got != components.end()) {
		got->second.addHandle(handle);
		return true;
	}
	return false;
}

ComponentTypeHandle* GameObject::getComponentTypeHandle(const ComponentType type) {
	auto got = components.find(type);
	if (got != components.end())
		return &got->second;
	return NULL;
}

bool GameObject::removeComponent(HandleManager *handleManager, const Handle handle) {
	auto got = components.find((ComponentType)handle.type);
	if (got != components.end()) {
		got->second.removeComponent(handleManager, handle);
		return true;
	}
	return false;
}

bool GameObject::removeComponents(HandleManager* handleManager, const ComponentType type) {
	auto got = components.find((ComponentType)handle.type);
	if (got != components.end()) {
		got->second.removeAllComponents(handleManager);
		return true;
	}
	return false;
}

void GameObject::removeSelf(HandleManager* handleManager) {
	handleManager->remove(handle);
	for (auto iter = components.begin(); iter != components.end(); iter++)
		iter->second.removeAllComponents(handleManager);
}

void GameObject::setHandle(Handle newHandle) {
	handle = newHandle;
}

Handle GameObject::getHandle() const { return handle; }