#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

typedef unsigned int uint32;

enum ComponentType : uint32 {
	NETWORK,
	PHYSICS,
	NUMBER_OF_COMPONENT_TYPES,
};

struct Handle
{
	Handle() : key(0), type(0), ifActive(false)
	{}

	Handle(uint32 newID, uint32 newType)
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
	uint32 type;
	bool ifActive;
};



#endif
