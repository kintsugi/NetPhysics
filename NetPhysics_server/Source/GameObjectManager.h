#ifndef GAME_OBJECT_MANAGER_H_INCLUDED
#define GAME_OBJECT_MANAGER_H_INCLUDED

#include "XLib.h"
#include "gameobject.h"
#include "gameobjectfilter.h"

typedef XLib::SharedPtr<GameObject> GameObjectPtr;

class HandleManager;
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
	Creates an empty GameObject in container and returns a pointer to it
	@param handleManager a pointer to the HandleManager object to store the object
	@return a pointer to the newly created GameObject
	*/
	GameObject* createGameObject(HandleManager &handleManager);
	
	/*
	Filters through container, returning a vector of the GameObject that meet the requirements.
	@param filter The GameObjectFilter describing the requirements of the returned object.
	@return a vector of handles to the GameObjects that match the filter.
	*/
	XLib::Vector<GameObject*> getGameObjects(const GameObjectFilter filter);

private:

	XLib::Vector<GameObjectPtr> container;
};

#endif