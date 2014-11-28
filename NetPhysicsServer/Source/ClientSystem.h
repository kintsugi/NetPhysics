#ifndef CLIENT_SYSTEM_H_INCLUDED
#define CLIENT_SYSTEM_H_INCLUDED

#include "System.h"
#include "RakNetTypes.h"
#include "ComponentList.h"
#include "NetworkHandleManager.h"

namespace NetPhysics {

	/*
		System for initializing and remove a client's game object, as well as
		checking if the client owning the game object has timed out.
	*/
	class ClientSystem : public System {
	public:
		ClientSystem();

		void update(Register &engineRegister);

		/*
		Creates a GameObject with a client component containing
		the client's, effectively adding him to the system.
		@param clientSystemAddress the clients systemAddress.
		*/
		void initializeClient(Register &engineRegister,
							  ::RakNet::RakNetGUID guid);

		/*
		TEMP: removes the owning clients game object
		*/
		void removeClient(Register &engineRegister,
						  NetworkKey networkID);

	private:

		ComponentList componentList;
	};
}

#endif