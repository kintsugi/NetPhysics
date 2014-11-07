#include "physicscomponent.h"
#include "bulletphysicsobject.h"
#include "handlemanager.h"

PhysicsComponent::PhysicsComponent(HandleManager& handleManager, BulletPhysicsObject& obj)
	:	bulletPhysicsObject(new BulletPhysicsObject(obj)),
		Component(handleManager.add(this, PHYSICS_COMPONENT)),
		dynamicsWorld(NULL), 
		rigidBody(NULL)
{
	//Creates the rigidbody with the data stored in member physicsComponent
	rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		*bulletPhysicsObject->mass,
		bulletPhysicsObject->motionState.get(),
		bulletPhysicsObject->collisionShape.get(),
		*bulletPhysicsObject->localInertia));
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

PhysicsComponent::~PhysicsComponent() {
	dynamicsWorld->removeRigidBody(rigidBody); delete rigidBody;
}