#ifndef GAME_OBJECT_MANAGER_H_INCLUDED
#define GAME_OBJECT_MANAGER_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef GAME_OBJECT_MANAGER_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */

#include "XLib.h"
#include "GameObjectFilter.h"

namespace NetPhysics {
	class HandleManager;
	class GameObject;

	/*
		Factory for GameObjects. Handles allocation, deletion, and retrieval.
	*/
	class GameObjectManager {
	public:

		/*
		Iterates through the container polling if any game object has expired
		@param handleManager a pointer to the HandleManager object the members of container are in.
		*/
		void update(HandleManager &handleManager);

		/*
		Stores a pointer to a game object within the container.
		@param gameObject a pointer to the object to be stored
		@return a pointer to the newly stored GameObject
		*/
		GameObject* createGameObject(GameObject* gameObject);

		/*
		Filters through container, returning a vector of the GameObject that meet the requirements.
		@param filter The GameObjectFilter describing the requirements of the returned object.
		@return a vector of handles to the GameObjects that match the filter.
		*/
		XLib::Vector<GameObject*> getGameObjects(const GameObjectFilter filter);

	private:

		XLib::Vector<XLib::SharedPtr<GameObject>> container;
	};
}

#endif