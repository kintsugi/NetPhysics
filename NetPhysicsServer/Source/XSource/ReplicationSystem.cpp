#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "ReplicationSystem.h"
#include "Register.h"
#include "GameObjectManager.h"
#include "GameObjectList.h"
#include "GameObject.h"
#include "ReplicationComponent.h"
#include "ReplicaKeyManager.h"
#include "NetworkMessage.h"
#include "BitStream.h"
#include "Stream.h"
#include "Logger.h"

using namespace NetPhysics;

ReplicationSystem::ReplicationSystem()
	: System(REGISTER)
	, componentList(REPLICATION_COMPONENT)
{}


void ReplicationSystem::update(Register &reg) {
	/*
	 * Communicate to slaves changes in the master game objects and apply
	 * the components updates.
	 */
#ifdef NET_PHYSICS_SERVER
	GameObjectList gameObjectList = GET_GAME_OBJECTS_WITH(componentList);
	GameObject* gameObject;
	ReplicationComponent* replicationComponent;
	for (
		gameObject = gameObjectList.next();
		gameObject;
		gameObject = gameObjectList.next())
	{
		replicationComponent = gameObject->getComponent<ReplicationComponent>(
			HANDLE_MANAGER,
			REPLICATION_COMPONENT);
		if (replicationComponent) {
			applyDifferential(reg, gameObject, replicationComponent);
			applyComponentReplication(reg, gameObject, replicationComponent);
			//TODO When a rComp is deleted?
		}
	}
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
		//TODO Client implementation.
#endif /* NET_PHYSICS_CLIENT */
}

void ReplicationSystem::receive(Register &reg, RakNet::BitStream& bsIn) {
	Stream<ReplicationMessage> in(bsIn, &ReplicationStreamFormatter());
	auto* message = in.streamPtr.get();
	switch (message->type) {
		case COMPONENT_MESSAGE: {
			componentMessageResponse(reg, *message);
			break;
		}
		//The client should be the only system receiving these messages
#ifdef NET_PHYSICS_CLIENT
		case CREATE_GAME_OBJECT: {
			createGameObjectResponse(reg, *message);
			break;
		}
		case DESTROY_GAME_OBJECT: {
			destroyGameObjectResponse(reg, *message);
			break;
		}
		case CREATE_COMPONENT: {
			createComponentResponse(reg, *message);
			break;
		}
		case DESTROY_COMPONENT: {
			destroyComponentResponse(reg, *message);
			break;
		}
#endif /* NET_PHYSICS_CLIENT */
		default: {
			DEBUG_LOG(WARNING_MSG, "Invalid message type.");
		}
	}
}

#ifdef NET_PHYSICS_SERVER
bool ReplicationSystem::addSlave(
	Register &reg,
	GameObject* gameObject,
	RakNet::RakNetGUID clientGUID)
{
	//insert pair and inform client to create the game object.
	auto* rComp = gameObject->getComponent<ReplicationComponent>(
		HANDLE_MANAGER,
		REPLICATION_COMPONENT);
	if (rComp) {
		ReplicaKey key = rComp->getReplicaKey();
		masterSlaveList.insert(std::make_pair(key, clientGUID));
		NetworkMessage::Package client(RAK_PEER_INTERFACE, clientGUID);
		RakNet::BitStream bsOut;
		bsOut.Write(CREATE_GAME_OBJECT);
		bsOut.Write(key);
		NetworkMessage::Send::replicationMessage(client, bsOut);
		//TODO components constructs in a new slave? (apply diff)
		return true;
	} else {
		std::string err("Slaving client to an invalid game Object");
		DEBUG_LOG(WARNING_MSG, err);
		return false;
	}
}
bool ReplicationSystem::removeSlave(
	Register &reg,
	GameObject* gameObject,
	RakNet::RakNetGUID clientGUID)
{
	//insert pair and inform client to create the game object.
	auto* rComp = gameObject->getComponent<ReplicationComponent>(
		HANDLE_MANAGER,
		REPLICATION_COMPONENT);
	if (rComp) {
		ReplicaKey key = rComp->getReplicaKey();
		auto range = masterSlaveList.equal_range(key);
		for (auto iter = range.first; iter != range.second; ++iter) {
			if (clientGUID == iter->second) {
				masterSlaveList.erase(iter);
				NetworkMessage::Package client(
					RAK_PEER_INTERFACE,
					clientGUID);
				RakNet::BitStream bsOut;
				bsOut.Write(DESTROY_GAME_OBJECT);
				bsOut.Write(key);
				NetworkMessage::Send::replicationMessage(client, bsOut);
				return true;
			}
		}
	} else
		DEBUG_LOG(
		WARNING_MSG,
		"Slaving client to a GameObject with no replication component");
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
	replicationComponent->clearDifferential();
	auto slaves = getSlaves(key);
	for (
		auto diffIter = differential.begin();
		diffIter != differential.end();
		++diffIter)
	{
		//If new component (map value is true)
		if (diffIter->second) {
			Component* component = gameObject->getComponent(
				HANDLE_MANAGER,
				diffIter->first);
			auto bsOut = component->construct();
			for (
				auto slaveIter = slaves.begin(); 
				slaveIter != slaves.end();
				++slaveIter)
			{
				NetworkMessage::Package client(RAK_PEER_INTERFACE, *slaveIter);
				RakNet::BitStream bsOut;
				bsOut.Write(CREATE_COMPONENT);	//ReplicationMessageType
				bsOut.Write(key);	//ReplicaKey
				bsOut.Write(diffIter->first);	//ComponentType
				bsOut.Write(bsOut);	//Constructor params
				NetworkMessage::Send::replicationMessage(client, bsOut);
			}
		//If removed component (map value is false)
		} else {
			for (
				auto slaveIter = slaves.begin();
				slaveIter != slaves.end();
				++slaveIter)
			{
				NetworkMessage::Package client(RAK_PEER_INTERFACE, *slaveIter);
				RakNet::BitStream bsOut;
				bsOut.Write(CREATE_COMPONENT);	//ReplicationMessageType
				bsOut.Write(key);	//ReplicaKey
				bsOut.Write(diffIter->first);	//ComponentType
				NetworkMessage::Send::replicationMessage(client, bsOut);
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
		component = gameObject->getComponent(HANDLE_MANAGER, *typeIter);
		if (component) {
			auto bsOut = component->send();
			if (bsOut != nullptr) {
				for (
					auto slaveIter = slaves.begin();
					slaveIter != slaves.end();
					++slaveIter)
				{
					NetworkMessage::Package client(
						RAK_PEER_INTERFACE,
						*slaveIter);
					RakNet::BitStream bsOut;
					bsOut.Write(CREATE_COMPONENT);	//ReplicationMessageType
					bsOut.Write(key);	//ReplicaKey
					bsOut.Write(*typeIter);	//ComponentType
					bsOut.Write(bsOut);	//Constructor params
					NetworkMessage::Send::replicationMessage(client, bsOut);
				}
			}
		}
	}
}
#endif /* NET_PHYSICS_SERVER */

ReplicationSystem::ReplicationMessage::ReplicationMessage(
	ReplicationMessageType type,
	ReplicaKey key)
	: type(type)
	, key(key)
	, compType(NULL_COMPONENT)
	, bsOut(nullptr)
{}

void ReplicationSystem::componentMessageResponse(
	Register &reg,
	ReplicationMessage &msg)
{
	//Send message to owning game object's component
	ReplicaKeyManager* rManager = &REPLICA_KEY_MANAGER;
	GameObject* gameObject = rManager->getGameObject(
		msg.key,
		HANDLE_MANAGER);
	Component* comp = gameObject->getComponent(
		HANDLE_MANAGER,
		msg.compType);
	comp->receive(*msg.bsOut);
}

#ifdef NET_PHYSICS_CLIENT
void ReplicationSystem::createGameObjectResponse(
	Register &reg,
	ReplicationMessage &msg)
{
	GameObject *gameObject = NEW_GAME_OBJECT;
	auto* rComp = new ReplicationComponent(REPLICA_KEY_MANAGER, msg.key);
	gameObject->addComponent(NEW_COMPONENT(rComp));
}

void ReplicationSystem::destroyGameObjectResponse(
	Register &reg,
	ReplicationMessage &msg)
{
	//Remove from rManager, remove from mem
	ReplicaKeyManager* rManager = &REPLICA_KEY_MANAGER;
	GameObject* gameObject = rManager->getGameObject(
		msg.key,
		HANDLE_MANAGER);
	rManager->remove(msg.key);
	gameObject->destroy(HANDLE_MANAGER);
}

void ReplicationSystem::createComponentResponse(
	Register &reg,
	ReplicationMessage &msg)
{
	
}

void ReplicationSystem::destroyComponentResponse(
	Register &reg,
	ReplicationMessage &msg)
{
	//Send message to owning game object's component
	ReplicaKeyManager* rManager = &REPLICA_KEY_MANAGER;
	GameObject* gameObject = rManager->getGameObject(
		msg.key,
		HANDLE_MANAGER);
	if (msg.compType != REPLICATION_COMPONENT)
		gameObject->removeComponent(HANDLE_MANAGER, msg.compType);
	else {
		std::string err("cannot remove replication comp with key: " + key);
		DEBUG_LOG(WARNING_MSG, err);
	}
}
#endif /* NET_PHYSICS_CLIENT */

ReplicationSystem::ReplicationMessage* ReplicationSystem::ReplicationStreamFormatter::format(
	RakNet::BitStream &inStream) 
{
	ReplicationSystem::ReplicationMessage* ret;
	ReplicationMessageType type;
	ReplicaKey key;
	inStream.ResetReadPointer();
	inStream.IgnoreBytes(sizeof(RakNet::MessageID));
	inStream.Read(type);
	inStream.Read(key);
	ret = new ReplicationSystem::ReplicationMessage(type, key);
	switch (type) {
		case ReplicationSystem::COMPONENT_MESSAGE: {
			inStream.Read(ret->compType);
			inStream.Read(ret->bsOut);
			break;
		}
//The client should be the only system receiving these messages
#ifdef NET_PHYSICS_CLIENT
		case ReplicationSystem::CREATE_COMPONENT: {
			inStream.Read(ret->compType);
			inStream.Read(ret->bsOut);
			break;
		}
		case ReplicationSystem::DESTROY_COMPONENT: {
			inStream.Read(ret->compType);
		}
#endif /* NET_PHYSICS_CLIENT */
	}
	return ret;
}