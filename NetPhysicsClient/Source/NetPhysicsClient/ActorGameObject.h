#pragma once
#include "NetPhysicsClient.h"

#include "XSource/Register.h"
#include "XSource/GameObject.h"

class ActorGameObject : public GameObject {
public:

	void ActorInit(Register &engineRegister) {
		handleManager = engineRegister.getHandleManager();
		handle = handleManager->add(this, GAME_OBJECT);
	}
	virtual void networkUpdate() {}

protected:

	HandleManager* getHandleManager() {return handleManager;}

private:

	HandleManager* handleManager;
};