#ifndef NET_COMP_MANAGER_H_INCLUDED
#define NET_COMP_MANAGER_H_INCLUDED

#include <vector>
#include <networkcomponent.h>

/*
	Container class for all NetworkComponents.
*/
class NetworkIDManager;

class NetworkComponentManager {
public:
	NetworkComponentManager() {};
	/*
		Creates a new component and returns a pointer to this. 
		@param peer pointer to current instance of RakNet
		@param manager reference to the networkIDManager the new component should use.
		@param guid the guid of the client connection the networkComponent should send to.
		@return pointer to the newly created NetworkComponent. Assign the pointer to the required entities.
	*/
	NetworkComponent* createNewComponent(RakNet::RakPeerInterface*, RakNet::NetworkIDManager*, RakNet::RakNetGUID);
private:
	std::vector<NetworkComponent*> networkComponents;
};



#endif