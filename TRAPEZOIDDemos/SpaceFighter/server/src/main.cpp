#include <iostream>
#include <string>
//#include "engine.h"
#include "TestEngineRegister.h"
#include "PlayerStateComponent.h"
#include "ComponentManager.h"


int main(int argc, char* argv[]) {
	TestEngineRegister testReg;
	testReg.init();
	HandleManager* handleManager = testReg.getHandleManager();
	ComponentManager* testCompManager = testReg.getComponentManager(PLAYER_STATE_COMPONENT);
	Handle compHandle = testCompManager->createComponent(new PlayerStateComponent(*handleManager, UNINITIALIZED));
	PlayerStateComponent* comp = (PlayerStateComponent*)handleManager->get(compHandle);
	//Engine engine;
	while (1) {
		//engine.update();
	}
}
		
