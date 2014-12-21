#ifndef FAMILY_H_INCLUDED
#define FAMILY_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef FAMILY_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "HandleManager.h"
#include "Handle.h"

namespace NetPhysics {
	class GameObject;

	class Family {
	public:

		Family() {}
		Family(Handle self);

		void setParent(GameObject* parent, HandleManager &handleManager);

		bool removeParent(HandleManager &handleManager);

		void addChild(GameObject* child);

		std::vector<Handle> getChildren();

		std::vector<GameObject*> getChildrenGameObjects();

		bool isChild(GameObject* gameObject);

		bool removeChildWithHandle(Handle childHandle);

		bool destroyChildWithHandle(
			Handle childHandle,
			HandleManager &handleManager);

		//TODO add getComponentsInChild(reg)

	private:

		//returns index value. -1 on failed query
		uint32_t findChild(Handle childHandle);
		bool removeChildAtIndex(uint32_t index);

		Handle selfHandle;
		Handle parentHandle;
		std::vector<Handle> children;

	};
}

#endif /* FAMILY_H_INCLUDED */