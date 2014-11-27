#ifndef COMPONENT_HANDLE_H_INCLUDED
#define COMPONENT_HANDLE_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Handle.h"			
#include "ComponentType.h"

/*
	Specializes a handle to specify a component type.
*/
namespace NetPhysics {
	struct ComponentHandle : public Handle {
		ComponentHandle(const Handle handle,
						const ComponentType type) :
						Handle(handle),
						componentType(type) {}
		const ComponentType componentType;
	};
}
#endif /* COMPONENT_HANDLE_H_INCLUDED */