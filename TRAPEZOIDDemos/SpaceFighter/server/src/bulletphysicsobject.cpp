#include "bulletphysicsobject.h"

BulletPhysicsObject::BulletPhysicsObject(BulletPhysicsObject& copy) {
	//Moves memory into this
	collisionShape = copy.collisionShape;
	motionState = copy.motionState;
	localInertia = copy.localInertia;
	mass = copy.mass;
}