#include "world.h"

physicsObject::physicsObject(physicsObject& copy) {
	//Moves memory into this
	collisionShape = std::move(copy.collisionShape);
	motionState = std::move(copy.motionState);
	localInertia = std::move(copy.localInertia);
	mass = std::move(copy.mass);
}

worldObjectComponent::worldObjectComponent(physicsObject& obj): physicsComponent(new physicsObject(obj)), dynamicsWorld(0) {
	//creates the rigidbody with the data stored in member physicsComponent
	rigidBody = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
	*physicsComponent.get()->mass.get(),
	physicsComponent.get()->motionState.get(),
	physicsComponent.get()->collisionShape.get(),
	*physicsComponent.get()->localInertia.get()));
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

World::World() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, 0, 0)); //Zero gravity
}
World::~World() {
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void World::update(float dt) {
	//Bullet physics doc says timeStep < maxSubSteps * fixedTimeStep or the simulation is mathematically losing time.
	int maxSubSteps = 1; float fixedTimeStep = 1/60.0f;
	while (dt/fixedTimeStep > maxSubSteps)
		maxSubSteps++;
	dynamicsWorld->stepSimulation(dt, maxSubSteps);
}

worldObjectComponent* World::createWorldObject(physicsObject &obj) {
	worldObjectComponent *worldObj = new worldObjectComponent(obj);
	objects.push_back(worldObj);
	dynamicsWorld->addRigidBody(objects.back()->getRigidBody());
	objects.back()->dynamicsWorld = dynamicsWorld;
	return objects.back();
}