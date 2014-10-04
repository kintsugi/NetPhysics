#include "engine.h"


Engine::Engine() {
	startServer();
	GameObject* test = gameObjectManager.createGameObject(&handleManager);
	test->addComponent(networkManager.createComponent(&handleManager, peer, &networkIDManager));
	std::vector<Handle> testhandle = test->getComponentTypeHandle(NETWORK)->getHandles();

	NetworkComponent* testcomp = test->getComponent<NetworkComponent>(&handleManager, testhandle[0]);
}
