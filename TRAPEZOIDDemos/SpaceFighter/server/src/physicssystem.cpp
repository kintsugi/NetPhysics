#include "physicssystem.h"
#include "physicscomponent.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

PhysicsSystem::PhysicsSystem() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, 0, 0)); //Zero gravity
}
PhysicsSystem::~PhysicsSystem() {
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void PhysicsSystem::update(float dt) {
	//Bullet physics doc says timeStep < maxSubSteps * fixedTimeStep or the simulation is mathematically losing time.
	int maxSubSteps = 1; float fixedTimeStep = 1 / 60.0f;
	while (dt / fixedTimeStep > maxSubSteps)
		maxSubSteps++;
	dynamicsWorld->stepSimulation(dt, maxSubSteps);
}

void PhysicsSystem::addToSystem(PhysicsComponent* component) {
	dynamicsWorld->addRigidBody(component->rigidBody);
	component->dynamicsWorld = dynamicsWorld;
}