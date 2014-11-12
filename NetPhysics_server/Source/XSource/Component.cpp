#ifdef CLIENT
	#include UE4_PROJECT_H
#endif
#include "Component.h"

Component::Component(Handle newHandle) : handle(newHandle) {}

Handle Component::getHandle() {
	return handle;
}

Handle Component::getParent() {
	return parent;
}

void Component::setParent(Handle parentHandle) {
	parent = parentHandle;
}
