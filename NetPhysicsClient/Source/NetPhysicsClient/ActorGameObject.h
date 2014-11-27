#pragma once
#include "NetPhysicsClient.h"

#include "XSource/Register.h"
#include "XSource/GameObject.h"
namespace NetPhysics {
	class ActorGameObject : public GameObject, public AActor {
	public:

		void ActorInit(NetPhysics::Register &engineRegister) {
			handleManager = engineRegister.getHandleManager();
			handle = handleManager->add(this, GAME_OBJECT);
		}
		virtual void networkUpdate() {}

	protected:

		HandleManager* getHandleManager() { return handleManager; }

	private:

		HandleManager* handleManager;
	};
}