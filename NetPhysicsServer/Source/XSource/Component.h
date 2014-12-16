#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Handle.h"
#include "ComponentHandle.h"
#include "Replica.h"

/*
	Base class for game object components
*/
namespace NetPhysics {
	class HandleManager;

	//Inherits replica as all components should have the ability to replicate
	//to clients.
	class Component : public Replica {
	public:

		Component(const ComponentType type, const Handle newHandle);

		Handle getHandle() const;
		ComponentHandle getComponentHandle() const;
		Handle getOwner() const;
		void setOwner(Handle ownerHandle);
		void destroy(HandleManager &handleManager);

	private:

		const ComponentHandle handle;
		Handle owner;
	};
}
#endif /* COMPONENT_H_INCLUDED */