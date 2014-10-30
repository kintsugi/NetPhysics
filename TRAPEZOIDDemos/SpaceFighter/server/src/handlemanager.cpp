#include "handlemanager.h"

void HandleManager::reset()
{
	entries.clear();
}


Handle HandleManager::add(void* dataPtr, const HandleType type)
{
	uint32 key = generateKey();
	entries.insert(std::make_pair(key, HandleEntry(type, dataPtr)));
	return Handle(key, type);
}


bool HandleManager::update(const Handle handle, void* dataPtr)
{
	//Attempt to find the value with the key handle.id
	auto got = entries.find(handle.key);
	//If not found, return false
	if (got == entries.end())
		return false;
	//If found and matches the handle.type, update dataPtr and return true
	else if(got->second.type == handle.type) {
		got->second.entry = dataPtr;
		return true;
	}
	//This point is reached if there were non matching types
	return false;
}


bool HandleManager::remove(const Handle handle)
{
	//Attempt to find the value with the key handle.id
	auto got = entries.find(handle.key);
	//If not found, return false
	if (got == entries.end())
		return false;
	//If found and matches the handle.type, erase the value.
	else if (got->second.type == handle.type) {
		entries.erase(got);
		return true;
	}
	//This point is reached if there were non matching types
	return false;
}


void* HandleManager::get(const Handle handle) const
{	
	//The pointer to return
	void* dataPtr = NULL;
	if (!get(handle, dataPtr))
		return NULL;
	return dataPtr;
}


bool HandleManager::get(const Handle handle, void*& out) const
{
	//Attempt to find the value with the key handle.id
	auto got = entries.find(handle.key);
	if (got == entries.end())
		return false;
	//If found and matches the handle.type, assign member entry to out
	else if (got->second.type == handle.type) {
		out = got->second.entry;
		return true;
	}
	//This point is reached if there were non matching types
	return false;
}

uint32 HandleManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}

