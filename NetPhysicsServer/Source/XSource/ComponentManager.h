#ifndef COMPONENT_MANAGER_H_INCLUDED
#define COMPONENT_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef COMPONENT_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include <memory>
#include <vector>
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
		ComponentHandle createComponent(
			HandleManager &handleManager,
			Component* component);

	private:

		const ComponentType managerType;
		std::vector<std::shared_ptr<Component>> container;
	};
}

#endif /* COMPONENT_MANAGER_H_INCLUDED */