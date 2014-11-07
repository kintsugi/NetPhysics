#pragma once
#include "SpaceFighter_client.h"
#include "Platform.h"

enum HandleType : uint32 {
	//Universal handle types.
	UNASSIGNED_TYPE,
	MESSENGER,
	SUBSCRIBER,
	//Server only handle types.
	GAME_OBJECT,
	NETWORK_COMPONENT,
	PHYSICS_COMPONENT,
	CLIENT_COMPONENT,
	PLAYER_STATE_COMPONENT,
	//Client only types.
	NETWORK_OBJECT,
};

struct Handle {
	Handle() : key(0), type(UNASSIGNED_TYPE), ifActive(false) {
	}

	Handle(uint32 newID, HandleType newType)
		: key(newID), type(newType), ifActive(true) {
	}

	inline bool operator==(const Handle& comp) {
		if (comp.key == key && comp.type == type)
			return true;
		else
			return false;
	}
	inline bool operator!=(const Handle& comp) {
		return !operator==(comp);
	}

	uint32 key;
	HandleType type;
	bool ifActive;
};
