#ifndef GAME_OBJECT_MANAGER_H_INCLUDED
#define GAME_OBJECT_MANAGER_H_INCLUDED

#include <vector>
#include "gameobject.h"

class HandleManager;

class GameObjectManager {
public:
	GameObjectManager() {}
	void update(HandleManager *handleManager);
	GameObject* createGameObject(HandleManager *handleManager);
private:
	std::vector<GameObject> container;
};

#endif