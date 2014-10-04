#include "bulletphysicsobject.h"

BulletPhysicsObject::BulletPhysicsObject(BulletPhysicsObject& copy) {
	//Moves memory into this
	collisionShape = std::move(copy.collisionShape);
	motionState = std::move(copy.motionState);
	localInertia = std::move(copy.localInertia);
	mass = std::move(copy.mass);
}