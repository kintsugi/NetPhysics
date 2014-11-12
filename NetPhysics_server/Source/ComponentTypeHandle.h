#ifndef COMPONENT_HANDLE_H_INCLUDED
#define COMPONENT_HANDLE_H_INCLUDED

#include "xlib.h"
#include "Handle.h"

class HandleManager;

/*
	Container for component handles. Used by the GameObject class to manage
	the Handles to its components.
*/
class ComponentTypeHandle {
public:
	ComponentTypeHandle(Handle newHandle) { addHandle(newHandle); }
	ComponentTypeHandle(XLib::Vector<Handle> newContainer) : container(newContainer) {}
	void addHandle(Handle handle);
	XLib::Vector<Handle> getHandles();
	bool removeComponent(HandleManager &handleManager, Handle handle);
	void removeAllComponents(HandleManager &handleManager);
	//returns the index of the handle if it has it, returns -1 if it doesnt.
	int getHandleIndex(Handle handle);
	unsigned int getCount();
private:
	XLib::Vector<Handle> container;
};

#endif