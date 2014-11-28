#include "ScriptSystem.h"
#include "XLib.h"
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

void ScriptSystem::update(Register &engineRegister, const double dt) {
	//Get game objects that contain a script component and update it.
	HandleManager* handleManager = engineRegister.getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister.getGameObjectManager();
	XLib::Vector<GameObject*> gameObjects = gameObjectManager->getGameObjectsWithComponents(componentList);
	ScriptComponent* scriptComponent = NULL;
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		scriptComponent = (*iter)->getComponent<ScriptComponent>(*handleManager, SCRIPT_COMPONENT);
		if (scriptComponent) {
			scriptComponent->update(dt);
		}
	}
}