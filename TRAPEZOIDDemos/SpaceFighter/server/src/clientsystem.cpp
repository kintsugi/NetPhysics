#include "clientsystem.h"

ClientSystem::ClientSystem() : filter(CLIENT_COMPONENT) {}

void ClientSystem::InitializeClient(HandleManager& handleManager,
									GameObjectManager &gameObjectManager,
									ClientManager& clientManager,
									RakNet::RakNetGUID guid)
{
	GameObject* clientGameObject = gameObjectManager.createGameObject(handleManager);
	clientGameObject->addComponent(clientManager.createComponent(handleManager, guid));
}