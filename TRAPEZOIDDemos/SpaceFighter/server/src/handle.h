#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

typedef unsigned int uint32;

enum HandleType : uint32 {
	UNASSIGNED_TYPE,
	GAME_OBJECT,
	NETWORK_COMPONENT,
	PHYSICS_COMPONENT,
	CLIENT_COMPONENT,
	MESSENGER,
	SUBSCRIBER,
};

struct Handle
{
	Handle() : key(0), type(UNASSIGNED_TYPE), ifActive(false)
	{}

	Handle(uint32 newID, HandleType newType)
		: key(newID), type(newType), ifActive(true)
	{}

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



#endif
