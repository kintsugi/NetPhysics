#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include "MessageIdentifiers.h"

enum Message {
	//Default message
	INVALID_MESSAGE = ID_USER_PACKET_ENUM + 1,
	//For updating a network component. Order sensitive (Message, networkID, ...)
	NETWORK_COMPONENT_MESSAGE,
};

#endif