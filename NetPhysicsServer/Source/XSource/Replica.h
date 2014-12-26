#ifndef REPLICA_H_INCLUDED
#define REPLICA_H_INCLUDED

#ifdef NET_PHYSICS_CLIENT
#undef REPLICA_H_INCLUDED	
#pragma once
#include "NetPhysicsClient.h"
#endif /* NET_PHYSICS_CLIENT */
#include <memory>

namespace RakNet {
	class BitStream;
}

//wip
namespace NetPhysics {
	//template<class T>
	class Replica {
	public:

		virtual std::shared_ptr<RakNet::BitStream> send() { return std::shared_ptr<RakNet::BitStream>(nullptr); }
		virtual void receive(RakNet::BitStream & bsIn) {}
		//void serialize(std::shared_ptr<T> newSerial) {lastSerial = newSerial;}

	protected:

		//std::shared_ptr<T> getLastSerial();

	private:

		//std::shared_ptr<T> lastSerial
	};
}

#endif /* REPLICA_H_INCLUDED */