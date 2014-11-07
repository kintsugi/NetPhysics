#ifdef CLIENT
	#include "SpaceFighter_client.h"
#endif /* CLIENT */

#include "EngineRegister.h"
#include "Component.h"
#include "ComponentManager.h"
#include "HandleManager.h"

void ComponentManager::update(EngineRegister &engineRegister, float dt) {
	HandleManager* handleManager = engineRegister.getManager<HandleManager>(HANDLE_MANAGER);
	for (auto iter = container.begin(); iter != container.end();) {
		if (!handleManager->get((*iter)->getHandle()))
			iter = container.erase(iter);
		else
			iter++;
	}
}