#ifndef GAME_OBJECT_FILTER_H_INCLUDED
#define GAME_OBJECT_FILTER_H_INCLUDED

#include "XLib.h"
#include "ComponentType.h"

#ifdef NET_PHYSICS_CLIENT
	#undef GAME_OBJECT_FILTER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

namespace NetPhysics {
	/*
	Acts as a filter to describe objects to the GameObjectManager for
	retrieval.
	*/
	class GameObjectFilter {
	public:

		GameObjectFilter() {}
		GameObjectFilter(const ComponentType type) { addToFilter(type); }
		GameObjectFilter(const XLib::Vector<ComponentType> types) : filterList(types) {}

		void addToFilter(const ComponentType type) {
#ifdef NET_PHYSICS_SERVER
			filterList.push_back(type);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			filterList.Add(type);
#endif /* NET_PHYSICS_CLIENT */
		}

		XLib::Vector<ComponentType> getFilterList() const { return filterList; }

	private:

		XLib::Vector<ComponentType> filterList;
	};
}

#endif /* GAME_OBJECT_FILTER_H_INCLUDED */