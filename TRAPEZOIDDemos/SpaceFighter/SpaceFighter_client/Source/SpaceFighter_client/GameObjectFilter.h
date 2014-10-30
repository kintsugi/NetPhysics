#pragma once

#include "SpaceFighter_client.h"

#include "handle.h"

/*
Acts as a filter to describe objects to the GameObjectManager for
retrieval.
*/
class GameObjectFilter {
public:
	GameObjectFilter() {};
	GameObjectFilter(const HandleType type) {filterList.Add(type);}
	GameObjectFilter(const TArray<HandleType> types) : filterList(types) {}
	void addToFilter(const HandleType type) {filterList.Add(type);}
	void addToFilter(const TArray<HandleType> types) {filterList.Append(types);}
	TArray<HandleType> getFilterList() const {return filterList;}
private:
	TArray<HandleType> filterList;
};