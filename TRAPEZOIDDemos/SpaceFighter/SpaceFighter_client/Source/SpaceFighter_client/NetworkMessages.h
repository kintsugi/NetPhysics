#pragma once

#include "SpaceFighter_client.h"
#include "MessageIdentifiers.h"

enum NetworkMessage {
	//Default message
	INVALID_MESSAGE = ID_USER_PACKET_ENUM + 1,
	//For updating a network component. Order sensitive (Message, networkID, ...)
	NETWORK_COMPONENT_MESSAGE,
	START_PLAYER,
};