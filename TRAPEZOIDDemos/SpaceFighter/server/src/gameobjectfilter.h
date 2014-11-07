#ifndef GAME_OBJECT_FILTER_H_INCLUDED
#define GAME_OBJECT_FILTER_H_INCLUDED

#include "xlib.h"
#include "handle.h"

/*
	Acts as a filter to describe objects to the GameObjectManager for
	retrieval. 
*/
class GameObjectFilter {
public:
	GameObjectFilter() {}
	GameObjectFilter(const HandleType type) { filterList.push_back(type); }
	GameObjectFilter(const XLib::Vector<HandleType> types) : filterList(types) {}
	void addToFilter(const HandleType type){ filterList.push_back(type); }
	void addToFilter(const XLib::Vector<HandleType> types) { filterList.insert(filterList.end(), types.begin(), types.end()); }
	XLib::Vector<HandleType> getFilterList() const { return filterList; }
private:
	XLib::Vector<HandleType> filterList;
};

#endif