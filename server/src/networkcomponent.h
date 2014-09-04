#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#include <memory>
#include "NetworkIDObject.h"

class NetworkComponent : private RakNet::NetworkIDObject {
friend class Network;
public:
	NetworkComponent(void(*f)(void *)) : updateFunctionPtr(f){}
	void Update(void *obj) {updateFunctionPtr(obj);}

private:
	std::unique_ptr<RakNet::BitStream> *in, *out;
	void(*updateFunctionPtr)(void *);
};


#endif