#ifndef HANDLE_MANAGER_H_INCLUDED
#define HANDLE_MANAGER_H_INCLUDED

#include "handle.h"
#include <unordered_map>

class HandleManager {
public:
	HandleManager() : nextAvailableKey(0){}

	//Clears the entries container
	void reset();
	/*
	Adds the sent pointer to the container
	@param dataPtr a pointer to the data to be stored
	@param type an uint32 as a identifier of the type
	@return the handle containing the the key value of the pointer
	*/
	Handle add(void* dataPtr, const HandleType type);
	/*
	Updates the pointer at denoted by param handle. can not change types
	@param handle the handle containing the key value of the pointer
	@param dataPtr a pointer to the data to be stored
	@return whether the update was successful. fails if handle is invalid
	*/
	bool update(const Handle handle, void* dataPtr);
	/*
	Erases the index denoted by the handle
	@param handle the handle containing the key value of the pointer
	@return whether the update was successful. false if handle is invalid
	*/
	bool remove(const Handle handle);
	/*
	Returns the data pointer denoted by handle.
	@param handle the handle containing the key value of the pointer
	@return the stored pointer. NULL if handle is invalid
	*/
	void* get(const Handle handle) const;
	/*
	Assigns the data pointer denoted by handle to out
	@param handle the handle containing the key value of the pointer
	@param out a NULL pointer to be assign to a data pointer if handle is valid
	@return whether the get was successful. false is handle is invalid
	*/
	bool get(const Handle handle, void*& out) const;
	/*

	*/
	template<typename T> bool getAs(const Handle handle, T& out) const;

private:
	uint32 nextAvailableKey;
	uint32 generateKey();

	struct HandleEntry {
		HandleEntry(const HandleType newType, void* dataPtr) : type(newType), entry(dataPtr) {}
		HandleType type;
		void* entry;
	};
	//Hash table of entries.
	std::unordered_map<uint32,HandleEntry> entries;
};


template<typename T>
inline bool HandleManager::getAs(const Handle handle, T& out) const {
	void* ret;
	const bool rv = Get(handle, ret);
	out = union_cast< T >(ret);
	return rv;
}




#endif
