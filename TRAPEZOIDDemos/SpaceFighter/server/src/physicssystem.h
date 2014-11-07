#ifndef PHYSICS_SYSTEM_H_INCLUDED
#define PHYSICS_SYSTEM_H_INCLUDED


class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class PhysicsComponent;

//Bullet physics simulator
class PhysicsSystem {
public:
	PhysicsSystem();
	~PhysicsSystem();
	/*
	Steps the simulation
	@param dt time to step the simulation (i.e. time between last server tick)
	*/
	void update(float dt);
	/*
	Creates the WorldObjectComponent in the simulation and returns the pointer
	@param obj reference to the physicsObject to create in the simulation
	@return pointer to the worldObject Component. Assign to required entities.
	*/
	void addToSystem(PhysicsComponent *component);
private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	

};

#endif