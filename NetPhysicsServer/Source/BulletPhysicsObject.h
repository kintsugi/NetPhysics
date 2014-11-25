#ifndef BULLET_PHYSICS_OBJECT_H_INCLUDED
#define BULLET_PHYSICS_OBJECT_H_INCLUDED

#include "XLib.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

//Container for bullet physics objects.
struct BulletPhysicsObject {

	BulletPhysicsObject(btCollisionShape* newCollisionShape,
						btDefaultMotionState* newMotionState,
						btScalar &newMass,
						btVector3 &newInertia);

	BulletPhysicsObject(BulletPhysicsObject& copy);
	XLib::SharedPtr<btCollisionShape> collisionShape;
	XLib::SharedPtr<btDefaultMotionState> motionState;
	XLib::SharedPtr<btScalar> mass;
	XLib::SharedPtr<btVector3> localInertia;
};


#endif