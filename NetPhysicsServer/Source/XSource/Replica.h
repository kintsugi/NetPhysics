#ifndef REPLICA_H_INCLUDED
#define REPLICA_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
#undef REPLICA_H_INCLUDED	
#pragma once
#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include "XLib.h"

namespace RakNet {
	class BitStream;
}

//wip
namespace NetPhysics {
	//template<class T>
	class Replica {
	public:

		virtual XLib::SharedPtr<RakNet::BitStream> send() { return NULL; }
		virtual void receive(XLib::SharedPtr<RakNet::BitStream>) {}
		//void serialize(XLib::SharedPtr<T> newSerial) {lastSerial = newSerial;}

	protected:

		//XLib::SharedPtr<T> getLastSerial();

	private:

		//XLib::SharedPtr<T> lastSerial
	};
}

#endif /* REPLICA_H_INCLUDED */