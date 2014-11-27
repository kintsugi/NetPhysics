#ifndef COMPONENT_MANAGER_H_INCLUDED
#define COMPONENT_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef COMPONENT_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
#include "ComponentHandle.h"

namespace NetPhysics {
	class Component;

	/*
		Generic container for storing game object components.
	*/
	class ComponentManager {
	public:

		ComponentManager(const ComponentType type);

		void update(HandleManager &handleManager);
		ComponentType getManagerType() const;
		ComponentHandle createComponent(Component* component);

	private:

		const ComponentType managerType;
		XLib::Vector<XLib::SharedPtr<Component>> container;
	};
}

#endif /* COMPONENT_MANAGER_H_INCLUDED */