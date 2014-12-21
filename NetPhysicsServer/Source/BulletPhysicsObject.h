#ifndef BULLET_PHYSICS_OBJECT_H_INCLUDED
#define BULLET_PHYSICS_OBJECT_H_INCLUDED

#include <memory>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

//Container for bullet physics objects.
namespace NetPhysics {
	struct BulletPhysicsObject {
		BulletPhysicsObject(
			btCollisionShape* newCollisionShape,
			btDefaultMotionState* newMotionState,
			btScalar &newMass,
			btVector3 &newInertia);

		BulletPhysicsObject(BulletPhysicsObject& copy);
		std::shared_ptr<btCollisionShape> collisionShape;
		std::shared_ptr<btDefaultMotionState> motionState;
		std::shared_ptr<btScalar> mass;
		std::shared_ptr<btVector3> localInertia;
	};
}

#endif