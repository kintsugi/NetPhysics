#include "SpaceFighter_client.h"
#include "HandleManager.h"

void HandleManager::reset() {
	entries.Reset();
}

Handle HandleManager::add(void* dataPtr, const HandleType type) {
	uint32 key = generateKey();
	entries.Add(key, HandleEntry(type, dataPtr));
	return Handle(key, type);
}

bool HandleManager::update(const Handle handle, void* dataPtr) {
	//Attempt to find the value with the key handle.key
	//auto got = entries.find(handle.key);
	HandleEntry* got = entries.Find(handle.key);
	//If not found, return false
	if (!got)
		return false;
	//If found and matches the handle.type, update dataPtr and return true
	else if (got->type == handle.type) {
		got->entry = dataPtr;
		return true;
	}
	//This point is reached if there were non matching types
	return false;
}

bool HandleManager::remove(const Handle handle) {
	//Attempt to find the value with the key handle.key
	HandleEntry* got = entries.Find(handle.key);
	//If not found, return false
	if (!got)
		return false;
	//If found and matches the handle.type, erase the value.
	else if (got->type == handle.type) {
		entries.Remove(handle.key);
		return true;
	}
	//This point is reached if there were non matching types
	return false;
}

void* HandleManager::get(const Handle handle) {
	//The pointer to return
	void* dataPtr = NULL;
	if (!get(handle, dataPtr))
		return NULL;
	return dataPtr;
}


bool HandleManager::get(const Handle handle, void*& out) {
	//Attempt to find the value with the key handle.id
	HandleEntry* got = entries.Find(handle.key);
	if (!got)
		return false;
	//If found and matches the handle.type, assign member entry to out
	else if (got->type == handle.type) {
		out = got->entry;
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