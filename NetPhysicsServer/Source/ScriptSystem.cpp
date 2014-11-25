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

ScriptSystem::ScriptSystem() : System(BOTH), filter(SCRIPT) {}

void ScriptSystem::update(Register *engineRegister, const double dt) {
	//Get game objects that contain a script component and update it.
	HandleManager* handleManager = engineRegister->getHandleManager();
	GameObjectManager* gameObjectManager = engineRegister->getGameObjectManager();
	XLib::Vector<GameObject*> gameObjects = gameObjectManager->getGameObjects(filter);
	ScriptComponent* scriptComponent = NULL;
	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++) {
		scriptComponent = (*iter)->getComponent<ScriptComponent>(*handleManager, SCRIPT);
		if (scriptComponent) {
			scriptComponent->update(dt);
		}
	}
}