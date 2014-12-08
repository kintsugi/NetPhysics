#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationSystem.h"

using namespace NetPhysics;

ReplicationSystem::ReplicationSystem() : System(REGISTER) {}

void ReplicationSystem::update(Register &engineRegister) {
	//TODO call each replication component send functions, apply component list changes, check from deleted replication components
	//
}

void ReplicationSystem::addClient(ReplicationComponent* replicationComponent,
	RakNet::RakNetGUID clientGUID) {
	//TODO message client to create game object and register it in the list
}
void ReplicationSystem::removeClient(ReplicationComponent* replicationComponent,
	RakNet::RakNetGUID clientGUID) {
	//message client to delete game object and remove it from the list
}