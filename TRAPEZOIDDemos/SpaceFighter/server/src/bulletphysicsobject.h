#ifndef BULLET_PHYSICS_OBJECT_H_INCLUDED
#define BULLET_PHYSICS_OBJECT_H_INCLUDED

#include <memory>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

//Container for bullet physics objects.
struct BulletPhysicsObject {
	BulletPhysicsObject() {}
	BulletPhysicsObject(BulletPhysicsObject& copy);
	std::unique_ptr<btCollisionShape> collisionShape;
	std::unique_ptr<btDefaultMotionState> motionState;
	std::unique_ptr<btScalar> mass;
	std::unique_ptr<btVector3> localInertia;
};


#endif