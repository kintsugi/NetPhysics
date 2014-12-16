#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "HandleManager.h"

using namespace NetPhysics;

HandleManager::HandleManager() : nextAvailableKey(0) {}

Handle HandleManager::add(void* dataPtr, const HandleType type) {
	HandleKey key = generateKey();
#ifdef NET_PHYSICS_SERVER
	entries.insert(std::make_pair(key, HandleEntry(type, dataPtr)));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	entries.Add(key, HandleEntry(type, dataPtr));
#endif /* NET_PHYSICS_CLIENT */
	return Handle(key, type);
}

bool HandleManager::update(const Handle handle, void* dataPtr) {
#ifdef NET_PHYSICS_SERVER
	//Attempt to find the value with the key handle.key
	auto got = entries.find(handle.key);
	//If not found, return false
	if (got == entries.end())
		return false;
	//If found and matches the handle.type, update dataPtr and return true
	else if (got->second.type == handle.type) {
		got->second.entry = dataPtr;
		return true;
	}
#endif /* NET_PHYSICS_SERVER */ 
#ifdef NET_PHYSICS_CLIENT
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
#endif /* NET_PHYSICS_CLIENT */
	//This point is reached if there were non matching types
	return false;
}

bool HandleManager::remove(const Handle handle) {
#ifdef NET_PHYSICS_SERVER
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
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
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
#endif /* NET_PHYSICS_CLIENT */
	//This point is reached if there were non matching types
	return false;
}

void* HandleManager::get(const Handle handle) const {
	//The pointer to return
	void* dataPtr = nullptr;
	if (!get(handle, dataPtr))
		return nullptr;
	return dataPtr;
}

bool HandleManager::get(const Handle handle, void*& out) const {
#ifdef NET_PHYSICS_SERVER
	//Attempt to find the value with the key handle.id
	auto got = entries.find(handle.key);
	if (got == entries.end())
		return false;
	//If found and matches the handle.type, assign member entry to out
	else if (got->second.type == handle.type) {
		out = got->second.entry;
		return true;
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	//Attempt to find the value with the key handle.id
	const HandleEntry* got = entries.Find(handle.key);
	if (!got)
		return false;
	//If found and matches the handle.type, assign member entry to out
	else if (got->type == handle.type) {
		out = got->entry;
		return true;
	}
#endif /* NET_PHYSICS_CLIENT */
	//This point is reached if there were non matching types
	return false;
}

HandleKey HandleManager::generateKey() {
	if (nextAvailableKey == 0) {
		nextAvailableKey++;
		return 0;
	}
	return nextAvailableKey++;
}

HandleManager::HandleEntry::HandleEntry(
	const HandleType newType,
	void* dataPtr)
	: type(newType)
	, entry(dataPtr)
{}
