#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#ifdef CLIENT
	#undef COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */
#include "Handle.h"
#include "ComponentHandle.h"

class HandleManager;

//Base class for components
class Component {
public:

	Component(ComponentType type, Handle newHandle);

	Handle getHandle();
	Handle getOwner();
	void setOwner(Handle ownerHandle);
	void destroy(HandleManager &handleManager);

private:

	ComponentHandle handle;
	Handle owner;
};

#endif /* COMPONENT_H_INCLUDED */