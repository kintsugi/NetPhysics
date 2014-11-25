#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "Component.h"
#include "HandleManager.h"
#ifdef SERVER
	#include "GameObject.h"
#endif /* SERVER */

Component::Component(ComponentType type,
					 Handle newHandle) : 
					 handle(newHandle, type) {}

Handle Component::getHandle() const {
	return handle;
}

Handle Component::getOwner() const {
	return owner;
}

void Component::setOwner(Handle ownerHandle) {
	owner = ownerHandle;
}

void Component::destroy(HandleManager &handleManager) {
#ifdef SERVER
	//Get the parent game object to remove the component from it.
	GameObject *gameObject = (GameObject*)handleManager.get(owner);
	if (gameObject) {
		gameObject->removeComponent(handleManager, handle.componentType);
	}
#endif /* SERVER */
	handleManager.remove(handle);
}