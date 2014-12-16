#ifndef COMPONENT_LIST_H_INCLUDED
#define COMPONENT_LIST_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef COMPONENT_LIST_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
#include "ComponentType.h"

namespace NetPhysics {
	class Component;

	/*
		Not used to store components or references to, used to easily a list of
		components.
	*/
	struct ComponentList {
		ComponentList() {}
		ComponentList(ComponentType type) { add(type); }

		void add(ComponentType type) {
#ifdef NET_PHYSICS_SERVER
			components.insert(std::make_pair(type, nullptr));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			components.Add(type, nullptr);
#endif /* NET_PHYSICS_CLIENT */
		}

		void add(ComponentType type, Component* component) {
#ifdef NET_PHYSICS_SERVER
			components.insert(std::make_pair(type, component));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			components.Add(type, component);
#endif /* NET_PHYSICS_CLIENT */
		}

		void remove(ComponentType type) {
#ifdef NET_PHYSICS_SERVER
			components.erase(type);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			components.Remove(type);
#endif /* NET_PHYSICS_CLIENT */
		}

		XLib::UnorderedMap<ComponentType, Component*> components;
	};
}

#endif /* COMPONENT_LIST_H_INCLUDED */