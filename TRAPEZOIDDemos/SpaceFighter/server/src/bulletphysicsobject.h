#ifndef BULLET_PHYSICS_OBJECT_H_INCLUDED
#define BULLET_PHYSICS_OBJECT_H_INCLUDED

#include <memory>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

//Container for bullet physics objects.
struct BulletPhysicsObject {
	BulletPhysicsObject() {}
	BulletPhysicsObject(BulletPhysicsObject& copy);
	std::shared_ptr<btCollisionShape> collisionShape;
	std::shared_ptr<btDefaultMotionState> motionState;
	btScalar mass;
	btVector3 localInertia;
};


#endif