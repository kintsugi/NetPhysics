#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "Component.h"
#include "HandleManager.h"
#ifdef NET_PHYSICS_SERVER
	#include "GameObject.h"
#endif /* NET_PHYSICS_SERVER */

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
#ifdef NET_PHYSICS_SERVER
	//Get the parent game object to remove the component from it.
	GameObject *gameObject = (GameObject*)handleManager.get(owner);
	if (gameObject) {
		gameObject->removeComponent(handleManager, handle.componentType);
	}
#endif /* NET_PHYSICS_SERVER */
	handleManager.remove(handle);
}