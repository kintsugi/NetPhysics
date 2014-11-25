#include "PhysicsComponent.h"
#include "HandleManager.h"
#include "BulletPhysicsObject.h"
#include "ComponentType.h"

PhysicsComponent::PhysicsComponent(HandleManager& handleManager,
								   BulletPhysicsObject& obj) :
								   bulletPhysicsObject(new BulletPhysicsObject(obj)),
								   Component(PHYSICS, handleManager.add(this, COMPONENT)),
								   dynamicsWorld(NULL), 
								   rigidBody(NULL) {
	//Creates the RigidBody with the data stored in member physicsComponent
	rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		*bulletPhysicsObject->mass,
		bulletPhysicsObject->motionState.get(),
		bulletPhysicsObject->collisionShape.get(),
		*bulletPhysicsObject->localInertia));

	/*
	Disabling deactivation for testing purposes, causes inactive objects to stop
	even if they are still moving.
	*/
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

PhysicsComponent::~PhysicsComponent() {
	dynamicsWorld->removeRigidBody(rigidBody); delete rigidBody;
}