#ifndef GAME_OBJECT_FILTER_H_INCLUDED
#define GAME_OBJECT_FILTER_H_INCLUDED

#include <vector>
#include "handle.h"

/*
	Acts as a filter to describe objects to the GameObjectManager for
	retrieval. 
*/
class GameObjectFilter {
public:
	GameObjectFilter() {}
	GameObjectFilter(const HandleType type) { filterList.push_back(type); }
	GameObjectFilter(const std::vector<HandleType> types) : filterList(types) {}
	void addToFilter(const HandleType type){ filterList.push_back(type); }
	void addToFilter(const std::vector<HandleType> types)  { filterList.insert(filterList.end(), types.begin(), types.end()); }
	std::vector<HandleType> getFilterList() const { return filterList; }
private:
	std::vector<HandleType> filterList;
};

#endif