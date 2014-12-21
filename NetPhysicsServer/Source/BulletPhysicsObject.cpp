#include "BulletPhysicsObject.h"

using namespace NetPhysics;

BulletPhysicsObject::BulletPhysicsObject(
	btCollisionShape* newCollisionShape,
	btDefaultMotionState* newMotionState,
	btScalar& newMass,
	btVector3& newInertia)
	: collisionShape(std::shared_ptr<btCollisionShape>(newCollisionShape))
	, motionState(std::shared_ptr<btDefaultMotionState>(newMotionState))
	, mass(std::shared_ptr<btScalar>(new btScalar(newMass)))
	, localInertia(std::shared_ptr<btVector3>(new btVector3(newInertia)))
{}

BulletPhysicsObject::BulletPhysicsObject(BulletPhysicsObject& copy) {
	collisionShape = copy.collisionShape;
	motionState = copy.motionState;
	localInertia = copy.localInertia;
	mass = copy.mass;
}