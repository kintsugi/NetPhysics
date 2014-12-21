#ifndef PHYSICS_COMPONENT_H_INCLUDED
#define PHYSICS_COMPONENT_H_INCLUDED

#include "Component.h"
#include "Handle.h"
#include "bulletphysicsobject.h"

class btRigidBody;
class btDiscreteDynamicsWorld;

//Container to safely handle creation/deletion of a bullet physics  object
namespace NetPhysics {
	class PhysicComponent : public Component {
	friend class PhysicSystem;
	public:

		PhysicComponent(HandleManager& handleManager, BulletPhysicsObject& obj);
		~PhysicComponent();

		//@return pointer to the rigidbody in the simulation
		btRigidBody* getRigidBody() const { return rigidBody; }
		//@ret pointer to the world the rigid body is in. Null is not placed in a world.
		btDiscreteDynamicsWorld* getWorld() const { return dynamicsWorld; }

	private:

		std::shared_ptr<BulletPhysicsObject> bulletPhysicsObject;
		btRigidBody* rigidBody;
		btDiscreteDynamicsWorld* dynamicsWorld;
	};
}


#endif