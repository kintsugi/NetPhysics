#ifndef NETWORK_HANDLE_OBJECT_H_INCLUDED
#define NETWORK_HANDLE_OBJECT_H_INCLUDED

#ifdef CLIENT
	#undef NETWORK_HANDLE_OBJECT_H_INCLUDED	
	#pragma once
	#include "NetPhysics_client.h"
#endif /* CLIENT */

typedef unsigned long long NetworkKey;

class NetworkHandleManager;

enum NetworkHandleType {
	UNDEFINED_TYPE,
};

class NetworkHandleObject {
public:

	NetworkHandleObject(void *newSuper) : super(newSuper), type(UNDEFINED_TYPE), key(0) {}
	NetworkHandleObject(void *super, NetworkHandleType newType) : type(UNDEFINED_TYPE), key(0) {}
	~NetworkHandleObject();

	void setNetworkHandleManager(NetworkHandleManager &networkHandleManager);
	NetworkKey getNetworkKey();
	NetworkHandleType getType();

	bool operator==(const NetworkHandleObject& comp);
	bool operator!=(const NetworkHandleObject& comp);

private:

	NetworkHandleManager* owningManager;
	void* super;
	NetworkHandleType type;
	NetworkKey key;

};

#endif