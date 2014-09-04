#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"


/*
Manages the physics world of the game.
*/
class World {
public:
	World();
	~World();

private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

};


#endif