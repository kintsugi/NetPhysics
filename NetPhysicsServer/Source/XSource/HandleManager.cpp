#ifdef CLIENT
	#include "NetPhysics_client.h"
#endif
#include "HandleManager.h"

void HandleManager::reset()
{
#ifdef SERVER
	entries.clear();
#endif /* SERVER */
#ifdef CLIENT
	entries.Reset();
#endif /* CLIENT */
}

Handle HandleManager::add(void* dataPtr, const HandleType type)
{
	uint32 key = generateKey();
#ifdef SERVER
	entries.insert(std::make_pair(key, HandleEntry(type, dataPtr)));
#endif /* SERVER */
#ifdef CLIENT
	entries.Add(key, HandleEntry(type, dataPtr));
#endif /* CLIENT */
	return Handle(key, type);
}

bool HandleManager::update(const Handle handle, void* dataPtr)
{
#ifdef SERVER

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

#endif /* SERVER */ 
#ifdef CLIENT

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

#endif /* CLIENT */
	//This point is reached if there were non matching types
	return false;
}

bool HandleManager::remove(const Handle handle)
{
#ifdef SERVER

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

#endif /* SERVER */
#ifdef CLIENT

	//Attempt to find the value with the key handle.key
	HandleEntry* got = entries.Find(handle.key);
	//If not found, return false
	if (!got)
		return false;
	//If found and matches the handle.type, erase the value.
	else if (got->type == handle.handleType) {
		entries.Remove(handle.key);
		return true;
	}

#endif /* CLIENT */
	//This point is reached if there were non matching types
	return false;
}

void* HandleManager::get(const Handle handle)
{	
	//The pointer to return
	void* dataPtr = NULL;
	if (!get(handle, dataPtr))
		return NULL;
	return dataPtr;
}

bool HandleManager::get(const Handle handle, void*& out)
{
#ifdef SERVER

	//Attempt to find the value with the key handle.id
	auto got = entries.find(handle.key);
	if (got == entries.end())
		return false;
	//If found and matches the handle.type, assign member entry to out
	else if (got->second.type == handle.type) {
		out = got->second.entry;
		return true;
	}

#endif /* SERVER */
#ifdef CLIENT

	//Attempt to find the value with the key handle.id
	HandleEntry* got = entries.Find(handle.key);
	if (!got)
		return false;
	//If found and matches the handle.type, assign member entry to out
	else if (got->type == handle.type) {
		out = got->entry;
		return true;
	}

#endif /* CLIENT */
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
