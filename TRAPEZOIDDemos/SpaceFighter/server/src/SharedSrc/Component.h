#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#ifdef CLIENT
	#undef MANAGER_H_INCLUDED	
	#pragma once
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

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