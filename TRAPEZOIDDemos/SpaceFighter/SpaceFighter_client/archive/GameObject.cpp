#include "SpaceFighter_client.h"
#include "GameObject.h"
#include "HandleManager.h"

GameObject::GameObject(HandleManager &handleManager) : messenger(handleManager) {
	handleManager.add(this, GAME_OBJECT);
}

bool GameObject::hasComponents(const GameObjectFilter filter) const {
	//if there is an handle type in the filter that is not in the map, return false
	TArray<HandleType> filterList = filter.getFilterList();
	for (auto iter = filterList.CreateIterator(); iter; iter++) {
		if (components.Contains(*iter) == 0)
			return false;
	}
	return true;
}

bool GameObject::addComponent(const Handle handle) {
	ComponentTypeHandle *got = components.Find(handle.type);
	if (got) {
		got->addHandle(handle);
		return true;
	} else if (!got) {
		components.Add(handle.type, ComponentTypeHandle(handle));
		return true;
	}
	return false;
}

ComponentTypeHandle* GameObject::getComponentTypeHandle(const HandleType type) {
	ComponentTypeHandle *got = components.Find(type);
	if (got)
		return got;
	return NULL;
}

bool GameObject::removeComponent(HandleManager &handleManager, const Handle handle) {
	ComponentTypeHandle *got = components.Find(handle.type);
	if (got) {
		got->removeComponent(handleManager, handle);
		return true;
	}
	return false;
}

bool GameObject::removeComponents(HandleManager &handleManager, const HandleType type) {
	ComponentTypeHandle *got = components.Find(handle.type);
	if (got) {
		got->removeAllComponents(handleManager);
		return true;
	}
	return false;
}

void GameObject::removeSelf(HandleManager &handleManager) {
	handleManager.remove(handle);
	for (auto iter = components.CreateIterator(); iter; iter.operator++())
		iter.Value().removeAllComponents(handleManager);
}

void GameObject::setHandle(Handle newHandle) {
	handle = newHandle;
}

Handle GameObject::getHandle() const {
	return handle;
}

Messenger* GameObject::getMessenger() {
	return &messenger;
}