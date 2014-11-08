#ifndef PHYSICS_MANAGER_H_INCLUDED
#define PHYSICS_MANAGER_H_INCLUDED

#include "xlib.h"
#include "handle.h"
#include "handlemanager.h"
#include "physicscomponent.h"

typedef std::shared_ptr<PhysicsComponent> PhysicsComponentPtr;

struct BulletPhysicsObject;

class PhysicsManager {
public:

	//Checks component validity flags to see if it should delete the component.
	void update(HandleManager &handleManager);
	/*
	Creates a PhysicsComponent object and stores it in member container. Returns a Handle.
	@param manager pointer to the HandleManager to contain the handle of the created component
	@param obj reference to a BulletPhysicsObject that describes the object in the world.
	@return handle of the created object.
	*/
	Handle createComponent(HandleManager &handleManager, BulletPhysicsObject& obj);

private:
	XLib::Vector<PhysicsComponentPtr> container;
};

#endif