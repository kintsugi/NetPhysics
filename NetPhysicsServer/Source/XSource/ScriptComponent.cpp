#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ScriptComponent.h"
#include "HandleManager.h"
#include "Register.h"
#include "GameObject.h"

using namespace NetPhysics;

ScriptComponent::ScriptComponent(Register &reg)
	: Component(SCRIPT_COMPONENT, reg.getHandleManager()->add(this, COMPONENT))
	, reg(&reg)
{
	start();
}

ScriptComponent::~ScriptComponent() {
	destroy();
}

Register* ScriptComponent::getRegister() {
	return reg;
}

GameObject* ScriptComponent::getGameObject() {
	HandleManager* handleManager = reg->getHandleManager();
	return reinterpret_cast<GameObject*>(handleManager->get(getOwner()));
}