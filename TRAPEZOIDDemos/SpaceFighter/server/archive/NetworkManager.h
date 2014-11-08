#ifndef NETWORK_MANAGER_H_INCLUDED
#define NETWORK_MANAGER_H_INCLUDED

#include "xlib.h"
#include "handle.h"
#include "networkcomponent.h"
#include "engineregister.h"

typedef std::shared_ptr<NetworkComponent> NetworkComponentPtr;

class HandleManager;
/*
	Factory for NetworkComponents. Handles allocation, deletion, and retrieval.
*/
class NetworkManager {
public:
	/*
	Iterates through the container polling if any component has expired.
	@param handleManager a pointer to the HandleManager object the members of container are in.
	*/
	void update(HandleManager &handleManager);
	/*
	Creates a NetworkComponent and returns a handle to it.
	@param handleManager a pointer to the HandleManager object to store the object
	@return the handle of the newly created object.
	*/
	Handle createComponent(EngineRegister &engineRegister, RakNet::RakPeerInterface* peer);

private:

	XLib::Vector<NetworkComponentPtr> container;
};

#endif