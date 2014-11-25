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

/*
	Base class for game object components
*/
class Component {
public:

	Component(const ComponentType type, 
			  const Handle newHandle);

	Handle getHandle() const;
	Handle getOwner() const;
	void setOwner(Handle ownerHandle);
	void destroy(HandleManager &handleManager);

private:

	const ComponentHandle handle;
	Handle owner;
};

#endif /* COMPONENT_H_INCLUDED */