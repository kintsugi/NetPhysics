#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "NetworkHandleObject.h"
#include "NetworkHandleManager.h"

NetworkHandleObject::~NetworkHandleObject() {
	if (owningManager) {
		owningManager->remove(key);
	}
}

void NetworkHandleObject::setNetworkHandleManager(NetworkHandleManager &networkHandleManager) {
	owningManager = &networkHandleManager;
	key = networkHandleManager.add(super, type);
}


NetworkKey NetworkHandleObject::getNetworkKey() {
	return key;
}

NetworkHandleType NetworkHandleObject::getType() {
	return type;
}

inline bool NetworkHandleObject::operator==(const NetworkHandleObject& comp) {
	if (comp.key == key && comp.type == type)
		return true;
	else
		return false;
}

inline bool NetworkHandleObject::operator!=(const NetworkHandleObject& comp) {
	return !operator==(comp);
}