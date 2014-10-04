#ifndef PHYSICS_COMPONENT_H_INCLUDED
#define PHYSICS_COMPONENT_H_INCLUDED

#include <memory>
#include "handle.h"
#include "bulletphysicsobject.h"

class btRigidBody;
class btDiscreteDynamicsWorld;

//Container to safely handle creation/deletion of a bullet physics  object
class PhysicsComponent {
friend class PhysicsSystem;
public:
	PhysicsComponent(BulletPhysicsObject& obj);
	~PhysicsComponent();
	//@return pointer to the rigidbody in the simulation
	btRigidBody* getRigidBody() const { return rigidBody; }
	//@retyrb pointer to the world the rigid body is in. Null is not placed in a world.
	btDiscreteDynamicsWorld* getWorld() const { return dynamicsWorld; }
	Handle getHandle();
	void setHandle(Handle handle);
private:
	Handle handle;
	std::unique_ptr<BulletPhysicsObject> bulletPhysicsObject;
	btRigidBody* rigidBody;
	btDiscreteDynamicsWorld* dynamicsWorld;
};




#endif