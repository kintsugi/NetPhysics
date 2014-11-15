#ifndef GAME_OBJECT_FILTER_H_INCLUDED
#define GAME_OBJECT_FILTER_H_INCLUDED

#include "XLib.h"
#include "ComponentType.h"

/*
	Acts as a filter to describe objects to the GameObjectManager for
	retrieval. 
*/
class GameObjectFilter {
public:
	GameObjectFilter() {}
	GameObjectFilter(const ComponentType type) { filterList.push_back(type); }
	GameObjectFilter(const XLib::Vector<ComponentType> types) : filterList(types) {}
	void addToFilter(const ComponentType type){ filterList.push_back(type); }
	void addToFilter(const XLib::Vector<ComponentType> types) { filterList.insert(filterList.end(), types.begin(), types.end()); }
	XLib::Vector<ComponentType> getFilterList() const { return filterList; }
private:
	XLib::Vector<ComponentType> filterList;
};

#endif