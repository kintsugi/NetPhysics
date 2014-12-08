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

		Family(Handle self);

		struct Child {
			Child(XLib::String tag, Handle handle);

			XLib::String tag;
			Handle handle;
		};

		void setParent(GameObject* parent, HandleManager &handleManager);
		void removeParent();
		void addChild(GameObject* child);
		XLib::Vector<Child> getChildren();
		bool isChild(GameObject* gameObject);

		/*
		WithTag functions does not guarantee that child is unique.
		Singular return functions retrieve the first match.
		Multiple return functions use all matches.

		Use WithHandle functions to guarantee the return child is unique
		getWithHandle to get a handle of a child is useless because you
		already have the handle.
		use isChild() to verify if a GO is a child.
		*/

		//WithHandle functions
		Child* getChildWithHandle(Handle childHandle);

		bool removeChildWithHandle(Handle childHandle);

		bool destroyChildWithHandle(
			Handle childHandle,
			HandleManager &handleManager);

		//WithTag functions
		Child* getChildWithTag(XLib::String tag);

		GameObject* getChildGameObjectWithTag(
			XLib::String tag,
			HandleManager &handleManager);

		XLib::Vector<Child> getChildrenWithTag(XLib::String tag);

		XLib::Vector<GameObject*> getChildrenGameObjectsWithTag(
			XLib::String tag,
			HandleManager &handleManager);

		//Returns true if there are multiple children with that tag
		bool removeChildWithTag(XLib::String tag);

		void removeChildrenWithTag(XLib::String tag);

		bool destroyChildWithTag(
			XLib::String tag,
			HandleManager &handleManager);

		void destroyChildrenWithTag(
			XLib::String tag, 
			HandleManager &handleManager);

		//checks if parent/children handles still exist. 
		void updateFamily(HandleManager &handleManager);

	private:

		//returns index value. -1 on failed query
		int findChild(Handle childHandle);
		int findChild(XLib::String tag);
		bool removeChildAtIndex(int index);

		Handle selfHandle;
		Handle parentHandle;
		XLib::Vector<Child> children;

	};
}

#endif /* FAMILY_H_INCLUDED */