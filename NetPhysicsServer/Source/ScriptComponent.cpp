#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ScriptComponent.h"
#include "HandleManager.h"
#include "Register.h"

using namespace NetPhysics;

ScriptComponent::ScriptComponent(
	HandleManager &handleManager,
	Register &engineRegister)
	: Component(SCRIPT_COMPONENT, handleManager.add(this, COMPONENT))
	, engineRegister(&engineRegister)
{
	start();
}

ScriptComponent::~ScriptComponent() {
	destroy();
}