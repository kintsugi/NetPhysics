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
#include "Logger.h"

using namespace NetPhysics;

ReplicationSystem::ReplicationSystem()
	: System(REGISTER)
	, componentList(REPLICATION_COMPONENT)
{}


void ReplicationSystem::update(Register &reg) {
	//TODO call each replication component send functions, apply component list changes, check from deleted replication components
#ifdef NET_PHYSICS_SERVER
	GameObjectList gameObjectList = reg.getGameObjectManager()->getGameObjectsWithComponents(componentList);
	GameObject* gameObject;
	ReplicationComponent* replicationComponent;
	for (gameObject = gameObjectList.next(); gameObject; gameObject = gameObjectList.next()) {
		replicationComponent = gameObject->getComponent<ReplicationComponent>(*reg.getHandleManager(), REPLICATION_COMPONENT);
		if (replicationComponent) {
			applyDifferential(reg, gameObject, replicationComponent);
			applyComponentReplication(reg, gameObject, replicationComponent);
			//
		}
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT

#endif /*  */
}

#ifdef NET_PHYSICS_SERVER
bool ReplicationSystem::addSlave(
	Register &reg,
	GameObject* gameObject,
	RakNet::RakNetGUID clientGUID)
{
	//insert pair and inform client to create the game object.
	ReplicationComponent* replicationComponent = gameObject->getComponent<ReplicationComponent>(*reg.getHandleManager(), REPLICATION_COMPONENT);
	if (replicationComponent) {
		ReplicaKey key = replicationComponent->getReplicaKey();
		masterSlaveList.insert(std::make_pair(key, clientGUID));
		NetworkMessage::Package client(reg.getRakPeerInstance(), clientGUID);
		NetworkMessage::Send::createGameObject(client, key);
		return true;
	} else
		DEBUG_LOG(WARNING_MSG, "Slaving client to a GameObject with no replication component");
	return false;

}
bool ReplicationSystem::removeSlave(
	Register &reg,
	GameObject* gameObject,
	RakNet::RakNetGUID clientGUID)
{
	//insert pair and inform client to create the game object.
	ReplicationComponent* replicationComponent = gameObject->getComponent<ReplicationComponent>(*reg.getHandleManager(), REPLICATION_COMPONENT);
	if (replicationComponent) {
		ReplicaKey key = replicationComponent->getReplicaKey();
		auto range = masterSlaveList.equal_range(key);
		for (auto iter = range.first; iter != range.second; ++iter) {
			if (clientGUID == iter->second) {
				masterSlaveList.erase(iter);
				NetworkMessage::Package client(reg.getRakPeerInstance(), clientGUID);
				NetworkMessage::Send::destroyGameObject(client, key);
				return true;
			}
		}
	} else
		DEBUG_LOG(WARNING_MSG, "Slaving client to a GameObject with no replication component");
	return false;
}

std::vector<RakNet::RakNetGUID> ReplicationSystem::getSlaves(ReplicaKey key) {
	std::vector<RakNet::RakNetGUID> ret;
	auto range = masterSlaveList.equal_range(key);
	for (auto iter = range.first; iter != range.second; ++iter)
		ret.push_back(iter->second);
	return ret;
}

void ReplicationSystem::applyDifferential(
	Register &reg,
	GameObject* gameObject,
	ReplicationComponent* replicationComponent)
{
	/*
	 * Check the differential for new and removed components
	 * New: Send to all slaves a REPLICATION_CREATE_COMPONENT message.
	 * Removed: Send to all slaves a REPLICATION_DESTROY_COMPONENT message.
	 */
	ReplicaKey key = replicationComponent->getReplicaKey();
	auto differential = replicationComponent->getDifferential();
	auto slaves = getSlaves(key);
	
	for (auto diffIter = differential.begin(); diffIter != differential.end(); ++diffIter) {
		//If new component
		if (diffIter->second) {
			Component* component = gameObject->getComponent(*reg.getHandleManager(), diffIter->first);
			auto bsOut = component->construct();
			for (auto slaveIter = slaves.begin(); slaveIter != slaves.end(); ++slaveIter) {
				NetworkMessage::Package client(reg.getRakPeerInstance(), *slaveIter);
				NetworkMessage::Send::createComponent(
					client,	//GUID
					key,	//ReplicaKey
					diffIter->first,	//ComponentType
					*bsOut);	//constructor params
			}
		//If removed component
		} else {
			for (auto slaveIter = slaves.begin(); slaveIter != slaves.end(); ++slaveIter) {
				NetworkMessage::Package client(reg.getRakPeerInstance(), *slaveIter);
				NetworkMessage::Send::destroyComponent(
					client,	//GUID
					key,	//ReplicaKey
					diffIter->first);	//ComponentType
			}
		}
	}
}

void ReplicationSystem::applyComponentReplication(
	Register &reg,
	GameObject* gameObject,
	ReplicationComponent* replicationComponent)
{
	ReplicaKey key = replicationComponent->getReplicaKey();
	auto slaves = getSlaves(key);
	auto types = replicationComponent->getTypes();
	Component* component;
	//Get component message. If not nullptr, send to all slaves.
	for (auto typeIter = types.begin(); typeIter != types.end(); ++typeIter) {
		component = gameObject->getComponent(*reg.getHandleManager(), *typeIter);
		if (component) {
			auto bsOut = component->send();
			if (bsOut != nullptr) {
				for (auto slaveIter = slaves.begin(); slaveIter != slaves.end(); ++slaveIter) {
					NetworkMessage::Package client(reg.getRakPeerInstance(), *slaveIter);
					NetworkMessage::Send::messageComponent(
						client,	//GUID
						key,	//ReplicaKey
						*typeIter,	//ComponentType
						*bsOut);	//Message
				}
			}
		}
	}
}

uint32_t NetworkMessage::Send::createGameObject(
	Package &package,
	ReplicaKey key)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)(REPLICATION_CREATE_GAME_OBJECT));
	bsOut.Write(key);
	return package.send(bsOut);
}
uint32_t NetworkMessage::Send::destroyGameObject(
	Package &package,
	ReplicaKey key)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)(REPLICATION_DESTROY_GAME_OBJECT));
	bsOut.Write(key);
	return package.send(bsOut);
}

uint32_t NetworkMessage::Send::createComponent(
	Package &package,
	ReplicaKey key,
	ComponentType type,
	RakNet::BitStream &constructorParams)
{
	RakNet::BitStream bsForm;
	bsForm.Write((RakNet::MessageID)(REPLICATION_CREATE_COMPONENT));
	bsForm.Write(key);
	bsForm.Write(type);
	bsForm.Write(constructorParams);
	return package.send(bsForm);
}
uint32_t NetworkMessage::Send::destroyComponent(
	Package &package,
	ReplicaKey key,
	ComponentType type)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)(REPLICATION_DESTROY_COMPONENT));
	bsOut.Write(key);
	bsOut.Write(type);
	return package.send(bsOut);
}

uint32_t NetworkMessage::Send::messageComponent(
	Package &package,
	ReplicaKey key,
	ComponentType type,
	RakNet::BitStream &bsOut)
{
	RakNet::BitStream bsForm;
	bsForm.Write((RakNet::MessageID)(REPLICATION_COMPONENT_MESSAGE));
	bsForm.Write(key);
	bsForm.Write(type);
	bsForm.Write(bsOut);
	return package.send(bsForm);
}

#endif /* NET_PHYSICS_SERVER */