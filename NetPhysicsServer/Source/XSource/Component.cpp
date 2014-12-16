#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Component.h"
#include "HandleManager.h"
#include "GameObject.h"


using namespace NetPhysics;

Component::Component(
	ComponentType type,
	Handle newHandle)
	: handle(newHandle, type) 
{}

Handle Component::getHandle() const {
	return handle;
}

ComponentHandle Component::getComponentHandle() const {
	return handle;
}

Handle Component::getOwner() const {
	return owner;
}

void Component::setOwner(Handle ownerHandle) {
	owner = ownerHandle;
}

void Component::destroy(HandleManager &handleManager) {
	//Get the parent game object to remove the component from it.
	GameObject *gameObject = (GameObject*)handleManager.get(owner);
	if (gameObject) {
		gameObject->removeComponent(handleManager, handle.componentType);
	}
	handleManager.remove(handle);
}