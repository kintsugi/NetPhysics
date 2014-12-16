#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationSystem.h"
#include "Register.h"
#include "GameObjectManager.h"
#include "GameObjectList.h"
#include "GameObject.h"
#include "ReplicationComponent.h"
#include "BitStream.h"

using namespace NetPhysics;

ReplicationSystem::ReplicationSystem()
	: System(REGISTER)
	, componentList(REPLICATION_COMPONENT)
{}


void ReplicationSystem::update(Register &reg) {
	//TODO call each replication component send functions, apply component list changes, check from deleted replication components
#ifdef NET_PHYSICS_SERVER
	processSends(reg);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT

#endif /*  */
}

#ifdef NET_PHYSICS_SERVER
void ReplicationSystem::addClient(ReplicationComponent* replicationComponent,
	RakNet::RakNetGUID clientGUID) {
	//TODO message client to create game object and register it in the list
}
void ReplicationSystem::removeClient(ReplicationComponent* replicationComponent,
	RakNet::RakNetGUID clientGUID) {
	//message client to delete game object and remove it from the list
}

void ReplicationSystem::processSends(Register &reg) {
	//Get GObj with replication components to process
	GameObjectList gameObjectList = reg.getGameObjectManager()->getGameObjectsWithComponents(componentList);
	GameObject* gameObject;
	ReplicationComponent* replicationComponent;
	for (gameObject = gameObjectList.next(); gameObject; gameObject = gameObjectList.next()) {
		replicationComponent = gameObject->getComponent<ReplicationComponent>(*reg.getHandleManager(), REPLICATION_COMPONENT);
		if (replicationComponent)
			send(reg, gameObject, replicationComponent);
	}

#ifdef NET_PHYSICS_SERVER
	for (auto iter = masterSlaveList.begin(); iter != masterSlaveList.end(); ++iter) {

	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
#endif /* NET_PHYSICS_CLIENT */
}

void ReplicationSystem::send(
	Register &reg,
	GameObject* gameObject,
	ReplicationComponent* replicationComponent)
{
	//Find slaves(guid) to the master(replication component)
	auto slaves = masterSlaveList.equal_range(replicationComponent->getReplicaKey());
	if (slaves.first != masterSlaveList.end()) {
		
		
	}
}

#endif /* NET_PHYSICS_SERVER */