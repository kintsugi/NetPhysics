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
	class Component {
	friend class ComponentManager;
	public:
		Component(ComponentType type);
		ComponentType getType();
		Handle getHandle() const;
		ComponentHandle getComponentHandle() const;
		Handle getOwner() const;
		void setOwner(Handle ownerHandle);
		void destroy(HandleManager &handleManager);

		//Component Replication virtual functions.
		virtual std::shared_ptr<RakNet::BitStream> send() { return nullptr; }
		virtual void receive(RakNet::BitStream &bsIn) {}
#ifdef NET_PHYSICS_SERVER
		virtual std::shared_ptr<RakNet::BitStream> construct()
		{
			return nullptr;
		}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		virtual Component* construct(RakNet::BitStream &bsIn)
		{
			return nullptr;
		}
#endif /* NET_PHYSICS_CLIENT */

	private:

		ComponentType type;
		ComponentHandle handle;
		Handle owner;
	};
}
#endif /* COMPONENT_H_INCLUDED */