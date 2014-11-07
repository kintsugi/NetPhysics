#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include "Handle.h"

//Base class for components
class Component {
public:
	Component(Handle newHandle);

	Handle getHandle();
	Handle getParent();
	void setParent(Handle parentHandle);

private:
	Handle handle;
	Handle parent;
};

#endif