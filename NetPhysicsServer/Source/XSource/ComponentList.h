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
	struct ComponentList {
		ComponentList() {}
		ComponentList(ComponentType type) {add(type);}

		void add(ComponentType type) {
#ifdef NET_PHYSICS_SERVER
			list.insert(std::make_pair(type, true));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			list.Add(type, true);
#endif /* NET_PHYSICS_CLIENT */
		}

		void remove(ComponentType type) {
#ifdef NET_PHYSICS_SERVER
			list.erase(type);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			list.Add(type, true);	//UE version of erase.
#endif /* NET_PHYSICS_CLIENT */
		}

		XLib::UnorderedMap<ComponentType, bool> list;
	};
}

#endif /* COMPONENT_LIST_H_INCLUDED */