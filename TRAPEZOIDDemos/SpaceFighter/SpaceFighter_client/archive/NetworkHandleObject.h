#pragma once

#include "SpaceFighter_client.h"

typedef uint64_t NetworkKey;

class NetworkHandleManager;

enum NetworkHandleType {
	UNDEFINED_TYPE,
};

class NetworkHandleObject {
public:

	NetworkHandleObject(void *super) : type(UNDEFINED_TYPE), key(0) {}
	NetworkHandleObject(void *super, NetworkHandleType newType) : type(UNDEFINED_TYPE), key(0) {}
	~NetworkHandleObject();

	void setNetworkHandleManager(NetworkHandleManager &networkHandleManager);
	NetworkKey getNetworkKey();
	void setNetworkKey(NetworkKey newKey);

	NetworkHandleType getType();

	inline bool operator==(const NetworkHandleObject& comp);
	inline bool operator!=(const NetworkHandleObject& comp);

private:

	NetworkHandleManager* owningManager;
	void* super;
	NetworkHandleType type;
	NetworkKey key;

};