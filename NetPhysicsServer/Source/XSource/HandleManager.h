#ifndef HANDLE_MANAGER_H_INCLUDED
#define HANDLE_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef HANDLE_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include <unordered_map>
#include "Handle.h"

 
namespace NetPhysics {
	class HandleManager {
	public:

		HandleManager();

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
		void* get(const Handle handle);

		/*
		Assigns the data pointer denoted by handle to out
		@param handle the handle containing the key value of the pointer
		@param out a NULL pointer to be assign to a data pointer if handle is valid
		@return whether the get was successful. false is handle is invalid
		*/
		bool get(const Handle handle, void*& out);

	private:

		HandleKey nextAvailableKey;
		HandleKey generateKey();
		struct HandleEntry {
			HandleEntry(
				const HandleType newType,
				void* dataPtr);

			HandleType type;
			void* entry;
		};
		std::unordered_map<HandleKey, HandleEntry> entries;
	};
}

#endif /* HANDLE_MANAGER_H_INCLUDED */
