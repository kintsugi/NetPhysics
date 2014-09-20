#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include <memory>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

//Container for bullet physics objects.
struct physicsObject {
	physicsObject() {}
	physicsObject(physicsObject&);
	std::unique_ptr<btCollisionShape> collisionShape;
	std::unique_ptr<btDefaultMotionState> motionState;
	std::unique_ptr<btScalar> mass;
	std::unique_ptr<btVector3> localInertia;
};

//Container to safely handle creation/deletion of a bullet physics  object
class worldObjectComponent {
friend class World;
public:
	worldObjectComponent(physicsObject&);
	~worldObjectComponent() {dynamicsWorld->removeRigidBody(rigidBody);delete rigidBody;}
	//@return pointer to the rigidbody in the simulation
	btRigidBody* getRigidBody() {return rigidBody;}
	btDiscreteDynamicsWorld* getWorld() {return dynamicsWorld;}
private:
	std::unique_ptr<physicsObject> physicsComponent;
	btRigidBody* rigidBody;
	btDiscreteDynamicsWorld* dynamicsWorld;
};

//Bullet physics simulator
class World {
public:
	World();
	~World();
	/*
		Steps the simulation
		@param dt time to step the simulation (i.e. time between last server tick)
	*/
	void update(float);
	/*
		Creates the WorldObjectComponent in the simulation and returns the pointer
		@param obj reference to the physicsObject to create in the similation
		@return pointer to the worldObject Component. Assign to required entities.
	*/
	worldObjectComponent* createWorldObject(physicsObject &);
private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<worldObjectComponent*> objects;

};


#endif