#include "physicscomponent.h"
#include "bulletphysicsobject.h"
#include "handlemanager.h"

PhysicsComponent::PhysicsComponent(HandleManager* handleManager, BulletPhysicsObject& obj)
	:	bulletPhysicsObject(obj),
		handle(handleManager->add(this, PHYSICS_COMPONENT)),
		dynamicsWorld(NULL), 
		rigidBody(NULL)
{
	//creates the rigidbody with the data stored in member physicsComponent
	rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		*bulletPhysicsObject.mass.get(),
		bulletPhysicsObject.motionState.get(),
		bulletPhysicsObject.collisionShape.get(),
		*bulletPhysicsObject.localInertia.get()));
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

PhysicsComponent::~PhysicsComponent() {
	dynamicsWorld->removeRigidBody(rigidBody); delete rigidBody;
}

Handle PhysicsComponent::getHandle() const {
	return handle;
}