#ifndef PHYSICS_COMPONENT_H_INCLUDED
#define PHYSICS_COMPONENT_H_INCLUDED

#include <memory>
#include "handle.h"
#include "bulletphysicsobject.h"

class btRigidBody;
class btDiscreteDynamicsWorld;
class HandleManager;

//Container to safely handle creation/deletion of a bullet physics  object
class PhysicsComponent {
friend class PhysicsSystem;
public:
	PhysicsComponent(HandleManager& handleManager, BulletPhysicsObject& obj);
	~PhysicsComponent();
	//@return pointer to the rigidbody in the simulation
	btRigidBody* getRigidBody() const { return rigidBody; }
	//@ret pointer to the world the rigid body is in. Null is not placed in a world.
	btDiscreteDynamicsWorld* getWorld() const { return dynamicsWorld; }
	Handle getHandle() const;
private:
	Handle handle;
	BulletPhysicsObject bulletPhysicsObject;
	btRigidBody* rigidBody;
	btDiscreteDynamicsWorld* dynamicsWorld;
};




#endif