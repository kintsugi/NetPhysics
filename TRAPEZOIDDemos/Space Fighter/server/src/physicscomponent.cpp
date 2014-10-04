#include "physicscomponent.h"
#include "bulletphysicsobject.h"

PhysicsComponent::PhysicsComponent(BulletPhysicsObject& obj) : bulletPhysicsObject(new BulletPhysicsObject(obj)), dynamicsWorld(NULL), rigidBody(NULL) {
	//creates the rigidbody with the data stored in member physicsComponent
	rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		*bulletPhysicsObject.get()->mass.get(),
		bulletPhysicsObject.get()->motionState.get(),
		bulletPhysicsObject.get()->collisionShape.get(),
		*bulletPhysicsObject.get()->localInertia.get()));
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

PhysicsComponent::~PhysicsComponent() {
	dynamicsWorld->removeRigidBody(rigidBody); delete rigidBody;
}

Handle PhysicsComponent::getHandle() { return handle; }
void PhysicsComponent::setHandle(Handle newHandle)  { handle = newHandle; }