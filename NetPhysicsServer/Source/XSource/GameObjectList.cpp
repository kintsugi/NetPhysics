#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "GameObjectList.h"

using namespace NetPhysics;

GameObjectList::GameObjectList() : index(0)
{}

GameObjectList::GameObjectList(XLib::Vector<GameObject*> gameObjects)
	: gameObjects(gameObjects)
	, index(0)
{}

GameObject* GameObjectList::next() {
	return index < gameObjects.size() ? step() : nullptr;
}

void GameObjectList::reset() {
	index = 0;
}

XLib::Vector<GameObject*> GameObjectList::get() {
	return gameObjects;
}

GameObject* GameObjectList::step() {
	GameObject* ret = gameObjects[index];
	index++;
	return ret;
}