#ifndef FAMILY_H_INCLUDED
#define FAMILY_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
	#undef FAMILY_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"
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

		XLib::Vector<Handle> getChildren();

		XLib::Vector<GameObject*> getChildrenGameObjects();

		bool isChild(GameObject* gameObject);

		bool removeChildWithHandle(Handle childHandle);

		bool destroyChildWithHandle(
			Handle childHandle,
			HandleManager &handleManager);

		//TODO add getComponentsInChild(ren)

	private:

		//returns index value. -1 on failed query
		uint32_t findChild(Handle childHandle);
		bool removeChildAtIndex(uint32_t index);

		Handle selfHandle;
		Handle parentHandle;
		XLib::Vector<Handle> children;

	};
}

#endif /* FAMILY_H_INCLUDED */