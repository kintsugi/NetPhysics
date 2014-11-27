#include "bulletphysicsobject.h"

using namespace NetPhysics;

BulletPhysicsObject::BulletPhysicsObject(btCollisionShape* newCollisionShape,
										 btDefaultMotionState* newMotionState,
										 btScalar& newMass,
										 btVector3& newInertia) {
	collisionShape = XLib::SharedPtr<btCollisionShape>(newCollisionShape);
	motionState = XLib::SharedPtr<btDefaultMotionState>(newMotionState);
	mass = XLib::SharedPtr<btScalar>(new btScalar(newMass));
	localInertia = XLib::SharedPtr<btVector3>(new btVector3(newInertia));
}

BulletPhysicsObject::BulletPhysicsObject(BulletPhysicsObject& copy) {
	collisionShape = copy.collisionShape;
	motionState = copy.motionState;
	localInertia = copy.localInertia;
	mass = copy.mass;
}