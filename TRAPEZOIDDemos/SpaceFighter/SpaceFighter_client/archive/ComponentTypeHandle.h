#pragma once

#include "SpaceFighter_client.h"
#include "Handle.h"

class HandleManager;

/*
Container for component handles. Used by the GameObject class to manage
the Handles to its components.
*/
class ComponentTypeHandle {
public:
	ComponentTypeHandle() {}

	ComponentTypeHandle(Handle newHandle) { addHandle(newHandle); }

	ComponentTypeHandle(TArray<Handle> newContainer) : container(newContainer) {}

	void addHandle(Handle handle);

	TArray<Handle> getHandles();

	bool removeComponent(HandleManager &handleManager, Handle handle);

	void removeAllComponents(HandleManager &handleManager);

	//returns the index of the handle if it has it, returns -1 if it doesnt.
	int getHandleIndex(Handle handle);
	unsigned int getCount();
private:
	TArray<Handle> container;
};