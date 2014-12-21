#ifndef GAME_OBJECT_LIST_H_INCLUDED
#define GAME_OBJECT_LIST_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICA_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif
#include <stdint.h>
#include <vector>

namespace NetPhysics {
	class GameObject;

	class GameObjectList {
	public:

		GameObjectList();
		GameObjectList(std::vector<GameObject*> gameObjects);

		GameObject* next();
		void reset();
		std::vector<GameObject*> get();

	private:

		int32_t index;
		std::vector<GameObject*> gameObjects;

		GameObject* step();
	};
}

#endif /* GAME_OBJECT_LIST_H_INCLUDED */