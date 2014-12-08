#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Family.h"
#include "GameObject.h"

using namespace NetPhysics;

Family::Family(Handle self) : selfHandle(self) {}

Family::Child::Child(
	XLib::String tag,
	Handle handle)
	: tag(tag)
	, handle(handle)
{}

void Family::setParent(GameObject* parent, HandleManager &handleManager) {
	//If there is already a parent, remove this child.
	if (parentHandle != Handle()) {
		GameObject* previousParent = reinterpret_cast<GameObject*>(handleManager.get(parentHandle));
		if (previousParent)
			previousParent->getFamily()->removeChildWithHandle(selfHandle);
	}
	parentHandle = parent->getHandle();
}

void Family::removeParent() {
	parentHandle = Handle();
}

void Family::addChild(GameObject* child) {
#ifdef NET_PHYSICS_SERVER
	children.push_back(Child(child->getTag(), child->getHandle()));
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	children.Add(Child(child->getTag(), child->getHandle()));
#endif /* NET_PHYSICS_CLIENT */
}

XLib::Vector<Family::Child> Family::getChildren() {
	return children;
}

bool Family::isChild(GameObject* gameObject) {
	//Adds one because findChild returns -1 on failed query.
	return findChild(gameObject->getHandle()) + 1 ? true : false;
}

Family::Child* Family::getChildWithHandle(Handle childHandle) {
	int childIndex = findChild(childHandle);
	Child* child = childIndex != -1 ? &children[childIndex] : NULL;
	return child;
}

bool Family::removeChildWithHandle(Handle childHandle) {
	return removeChildAtIndex(findChild(childHandle));
}

bool Family::destroyChildWithHandle(
	Handle childHandle,
	HandleManager &handleManager)
{
	if (removeChildWithHandle(childHandle)) {
		GameObject* childGameObject = reinterpret_cast<GameObject*>(handleManager.get(childHandle));
		if (childGameObject) {
			childGameObject->destroy(handleManager);
			return true;
		}
	}
	return false;
}

Family::Child* Family::getChildWithTag(XLib::String tag) {
	int childIndex = findChild(tag);
	Child* child = childIndex != -1 ? &children[childIndex] : NULL;
	return child;
}

int Family::findChild(Handle childHandle) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		if (iter->handle == childHandle)
			return iter - children.begin();
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = children.CreateIterator(); iter; iter++) {
		if (iter->handle == childHandle)
			return iter.GetIndex();
	}
#endif /* NET_PHYSICS_CLIENT */
}

int Family::findChild(XLib::String tag) {
#ifdef NET_PHYSICS_SERVER
	for (auto iter = children.begin(); iter != children.end(); iter++) {
		if (iter->tag == tag)
		return iter - children.begin();
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	for (auto iter = children.CreateIterator(); iter; iter++) {
		if (iter->tag == tag)
			return iter.GetIndex();
	}
#endif /* NET_PHYSICS_CLIENT */
	return -1;
}

bool Family::removeChildAtIndex(int index) {
	if (index != -1) {
		children.erase(children.begin() + index);
		return true;
	} else
		return false;
}