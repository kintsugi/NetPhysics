#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ScriptSystem.h"

//Identifying filter type
#include "ComponentType.h"
//Register & Manager includes
#include "Register.h"
#include "HandleManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
//ScriptComponent fuctionality
#include "ScriptComponent.h"

using namespace NetPhysics;

ScriptSystem::ScriptSystem() : System(BOTH), componentList(SCRIPT_COMPONENT) {}

void ScriptSystem::update(Register &reg, const double dt) {
#ifdef NET_PHYSICS_SERVER
	//Get game objects that contain a script component and update it.
	HandleManager* handleManager = reg.getHandleManager();
	GameObjectManager* gameObjectManager = reg.getGameObjectManager();

	GameObjectList gameObjectList = gameObjectManager->getGameObjectsWithComponents(componentList);
	GameObject* gameObject;
	ScriptComponent* scriptComponent = nullptr;
	for (gameObject = gameObjectList.next(); gameObject; gameObject = gameObjectList.next()) {
		scriptComponent = gameObject->getComponent<ScriptComponent>(*handleManager, SCRIPT_COMPONENT);
		if (scriptComponent) {
			scriptComponent->update(dt);
		}
	}
#endif
}