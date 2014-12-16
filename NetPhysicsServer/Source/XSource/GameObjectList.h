#ifndef GAME_OBJECT_LIST_H_INCLUDED
#define GAME_OBJECT_LIST_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef REPLICA_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif
#include "XLib.h"

namespace NetPhysics {
	class GameObject;

	class GameObjectList {
	public:

		GameObjectList();
		GameObjectList(XLib::Vector<GameObject*> gameObjects);

		GameObject* next();
		void reset();
		XLib::Vector<GameObject*> get();

	private:

		int32_t index;
		XLib::Vector<GameObject*> gameObjects;

		GameObject* step();
	};
}

#endif /* GAME_OBJECT_LIST_H_INCLUDED */