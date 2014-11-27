#ifndef PHYSIC_SYSTEM_H_INCLUDED
#define PHYSIC_SYSTEM_H_INCLUDED

#include "System.h"

//bt forward declarations
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace NetPhysics {
	class PhysicComponent;

	/*
		Basic physic simulator, designed for non-contraint, single shape objects.
	*/
	class PhysicSystem : public System {
	public:

		PhysicSystem();
		~PhysicSystem();
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
		void addToSimulation(PhysicComponent *component);

	private:

		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
	};
}

#endif /* PHYSIC_SYSTEM_H_INCLUDED */