#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef GAME_OBJECT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#include <string>
#include "XLib.h"
#include "ComponentHandle.h"
#include "Messenger.h"

namespace NetPhysics {
	struct ComponentList;

	/*
	GameObject class encapsulates handles to components.
	Access added components by using HandleManager::Get
	Handle::type denotes the type of the component.
	A GameObject cannot have multiple of the same component, or things get weird.
	*/
	class GameObject {
	public:

		GameObject(HandleManager& handleManager);
		/*
		Adds the component that Handle points to to the game object.
		@param handle the handle of the components
		@return true if successfully added, false if componentHandle is an invalid
		handle or if another component exists of that type.
		*/
		bool addComponent(HandleManager &handleManager,
						  const ComponentHandle componentHandle);

		/*
		Returns the component specified
		@param handleManager pointer to engine instance of HandleManager
		@param type specifying what type of component to return.
		@return null if no component exists of that type.
		*/
		template<class T>
		T* getComponent(HandleManager &handleManager,
						const ComponentType type);

		/*
		Destroys component of the specified type.
		*/
		void removeComponent(HandleManager &handleManager,
							 const ComponentType type);

		//Returns true if a component of the specified type exists.
		bool hasComponent(const ComponentType type);

		//Returns true if all component specified in the filter exist.
		bool hasComponents(const ComponentList &componentList);

		/*
		Remove the handle of the object and all handles of its component from the handle manager
		Note: when a GameObject of component does not have a valid handle, its manager deletes it next update.
		All subsequent calls to the data the handle pointed to will be null
		*/
		void destroy(HandleManager &handleManager);

		bool addChild(Handle child);	//Returns false if already a child.
		bool removeChild(Handle child); //Returns false if no match.
		void removeChildren();
		XLib::Vector<Handle> getChildren();
		bool isChild(Handle child);
		Handle getHandle() const;
		XLib::String getTag();
		void setTag(XLib::String newTag);

	protected:
#ifdef NET_PHYSICS_CLIENT
		//Client needs an empty default constructor for ActorGameObject inheritance
		GameObject() {}
#endif /* NET_PHYSICS_CLIENT */
		Handle handle;
		XLib::String tag;

	private:
		XLib::UnorderedMap<ComponentType, ComponentHandle> components;
		XLib::Vector<Handle> children;
	};

	template<class T>
	T* GameObject::getComponent(HandleManager &handleManager, const ComponentType type) {
#ifdef NET_PHYSICS_SERVER
		auto got = components.find(type);
		if (got != components.end()) {
			return (T*)handleManager.get(got->second);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		ComponentHandle* got = components.Find(type);
		if (got) {
			return (T*)handleManager.get(*got);
#endif /* NET_PHYSICS_CLIENT */
		}
		return NULL;
	}
}
#endif /* GAME_OBJECT_H_INCLUDED */
