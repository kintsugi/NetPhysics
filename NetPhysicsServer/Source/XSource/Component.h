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
	public:

		Component(const ComponentType type, const Handle newHandle);

		Handle getHandle() const;
		ComponentHandle getComponentHandle() const;
		Handle getOwner() const;
		void setOwner(Handle ownerHandle);
		void destroy(HandleManager &handleManager);

		//Component Replication virtual functions.
		virtual std::shared_ptr<RakNet::BitStream> send() { return nullptr; }
		virtual void receive(RakNet::BitStream &bsIn) {}
		virtual std::shared_ptr<RakNet::BitStream> construct(
			RakNet::BitStream *bsIn = NULL)
		{
			return nullptr;
		}

	private:

		const ComponentHandle handle;
		Handle owner;
	};
}
#endif /* COMPONENT_H_INCLUDED */