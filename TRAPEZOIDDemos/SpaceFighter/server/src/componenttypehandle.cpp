#include "componenttypehandle.h"
#include "handlemanager.h"

void ComponentTypeHandle::addHandle(Handle handle) {
	container.push_back(handle);
}

std::vector<Handle> ComponentTypeHandle::getHandles() {
	return container;
}

bool ComponentTypeHandle::removeComponent(HandleManager &handleManager, Handle handle) {
	for (auto iter = container.begin(); iter != container.end(); iter++) {
		if (handle == *iter) {
			handleManager.remove(handle);
			container.erase(iter);
			return true;
		}
	}
	return false;
}

void ComponentTypeHandle::removeAllComponents(HandleManager &handleManager) {
	for (auto iter = container.begin(); iter != container.end(); iter++)
		handleManager.remove(*iter);
	container.clear();
}

int ComponentTypeHandle::getHandleIndex(Handle handle) {
	for (unsigned int i = 0; i < container.size(); i++) {
		if (container[i] == handle)
			return i;
	}
	return -1;
}

unsigned int ComponentTypeHandle::getCount() {
	return container.size();
}