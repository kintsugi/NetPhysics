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
			Component* nullComponent = nullptr;
			components.insert_X(type, nullComponent);
		}

		void add(ComponentType type, Component* component) {
			components.insert_X(type, component);
		}

		void remove(ComponentType type) {
			components.erase_X(type);
		}

		XLib::UnorderedMap<ComponentType, Component*> components;
	};
}

#endif /* COMPONENT_LIST_H_INCLUDED */