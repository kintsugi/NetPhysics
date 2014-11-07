#include "SpaceFighter_client.h"
#include "componenttypehandle.h"
#include "handlemanager.h"

void ComponentTypeHandle::addHandle(Handle handle) {
	container.Add(handle);
}

TArray<Handle> ComponentTypeHandle::getHandles() {
	return container;
}

bool ComponentTypeHandle::removeComponent(HandleManager &handleManager, Handle handle) {
	for (auto iter = container.CreateIterator(); iter; iter++) {
		if (handle == *iter) {
			handleManager.remove(handle);
			container.RemoveAt(iter.GetIndex());
			iter--;
			return true;
		}
	}
	return false;
}

void ComponentTypeHandle::removeAllComponents(HandleManager &handleManager) {
	for (auto iter = container.CreateIterator(); iter; iter++)
		handleManager.remove(*iter);
	container.Reset();
}

int ComponentTypeHandle::getHandleIndex(Handle handle) {
	for (auto iter = container.CreateIterator(); iter; iter++)  {
		if (*iter == handle)
			return iter.GetIndex();
	}
	return -1;
}

unsigned int ComponentTypeHandle::getCount() {
	return container.Max();
}