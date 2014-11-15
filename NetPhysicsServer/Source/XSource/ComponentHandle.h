#ifndef COMPONENT_HANDLE_H_INCLUDED
#define COMPONENT_HANDLE_H_INCLUDED

#ifdef CLIENT
	#undef COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

#include "Handle.h"
#include "ComponentType.h"

struct ComponentHandle : public Handle {
	ComponentHandle(Handle handle, ComponentType type) : Handle(handle), componentType(type) {}
	ComponentType componentType;
};

#endif /* COMPONENT_HANDLE_H_INCLUDED */