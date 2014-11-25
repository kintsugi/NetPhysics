#ifndef GAME_OBJECT_FILTER_H_INCLUDED
#define GAME_OBJECT_FILTER_H_INCLUDED

#include "XLib.h"
#include "ComponentType.h"

#ifdef CLIENT
	#undef GAME_OBJECT_FILTER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */

/*
	Acts as a filter to describe objects to the GameObjectManager for
	retrieval. 
*/
class GameObjectFilter {
public:

	GameObjectFilter() {}
	GameObjectFilter(const ComponentType type) {addToFilter(type);}
	GameObjectFilter(const XLib::Vector<ComponentType> types) : filterList(types) {}

	void addToFilter(const ComponentType type){ 
#ifdef SERVER
		filterList.push_back(type);
#endif /* SERVER */
#ifdef CLIENT
		filterList.Add(type);
#endif /* CLIENT */
	}

	XLib::Vector<ComponentType> getFilterList() const { return filterList; }

private:

	XLib::Vector<ComponentType> filterList;
};

#endif /* GAME_OBJECT_FILTER_H_INCLUDED */