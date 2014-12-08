#include "PhysicSystem.h"

#include "PhysicComponent.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

using namespace NetPhysics;

PhysicSystem::PhysicSystem()
	: System(DELTA_TIME)
	, broadphase(new btDbvtBroadphase())
	, collisionConfiguration(new btDefaultCollisionConfiguration())
	, dispatcher(new btCollisionDispatcher(collisionConfiguration))
	, solver(new btSequentialImpulseConstraintSolver())
	, dynamicsWorld(new btDiscreteDynamicsWorld(
		dispatcher, broadphase, solver, collisionConfiguration))
{
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	dynamicsWorld->setGravity(btVector3(0, 0, 0)); //Zero gravity
}

PhysicSystem::~PhysicSystem() {
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void PhysicSystem::update(float dt) {
	//Bullet physics doc says timeStep < maxSubSteps * fixedTimeStep or the simulation is mathematically losing time.
	int maxSubSteps = 1; float fixedTimeStep = 1 / 60.0f;
	while (dt / fixedTimeStep > maxSubSteps)
		maxSubSteps++;
	dynamicsWorld->stepSimulation(dt, maxSubSteps);
}

void PhysicSystem::addToSimulation(PhysicComponent* component) {
	dynamicsWorld->addRigidBody(component->rigidBody);
	component->dynamicsWorld = dynamicsWorld;
}