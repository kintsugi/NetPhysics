#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#ifdef CLIENT
	#undef NETWORK_COMPONENT_H_INCLUDED	
	#pragma once
	#include "NetPhysicsClient.h"
#endif /* CLIENT */


#include "XLib.h"					//Shared source between client/server
#include "Component.h"				//Base class
#include "NetworkHandleObject.h"	//Base class
#include "Stream.h"					//Stream containers

class HandleManager;

/*
	Class for handling inbound and outbound data for an entity between the client and the server.
	Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent : public Component, public NetworkHandleObject {
public:

	/*
	@param handleManager reference to a handleManager to manage this object
	@param peer pointer to the server instance of RakNet
	@param manager pointer to a NetworkIDManager object for this object
	*/
	NetworkComponent(HandleManager &handleManager,
					 NetworkHandleManager &networkHandleManager,
					 RakNet::RakPeerInterface* peer);

	/*
	@param handleManager reference to a handleManager to manage this object
	@param peer pointer to the server instance of RakNet
	@param manager pointer to a NetworkIDManager object for this object
	@param formatter virtual class that determines how to format BitStreams. Uses default if NULL
	*/
	NetworkComponent(HandleManager& handleManager,
					 NetworkHandleManager &networkHandleManager,
					 RakNet::RakPeerInterface* peer,
					 StreamFormatter* newFormatter);

	/*
	Sets the formatter the object uses to format BitStreams.
	@param newFormatter pointer to either a StreamFormatter base or abstract class
	*/
	void setFormatter(const XLib::SharedPtr<StreamFormatter> newFormatter);

	//Returns a pointer to the StreamFormatter of this object. NULL if it has not been set.
	XLib::SharedPtr<StreamFormatter> getFormatter() const;

	/*
	Adds a BitStream to the container.
	@param inBS the BitStream to add.
	*/
	void addBitStream(XLib::SharedPtr<RakNet::BitStream> inBS);
	
	//Returns the inBitStreams vector.
	XLib::Vector<XLib::SharedPtr<RakNet::BitStream>> getBitStreams() const;

	//Returns the last index of the inBitStreams vector and removes it. NULL if empty. 
	XLib::SharedPtr<RakNet::BitStream> popBitStream();

	//Clears the inBitStreams vector.
	void clearBitStreams();
	
	/*
	Returns a vector of Stream objects specialized to type T using the
	StreamFormatter object pointed to in member formatter. Has size 0 if
	inBitStreams has size 0 or if the StreamFormatter has not been set.
	*/
	template<class T>
	XLib::Vector<Stream<T>> getStreams() const;

	/*
	Returns a Stream object specialized to type T using the StreamFormatter 
	object pointed to in member formatter. Uses the first index of the
	inBitStreams vector and removes it. Stream::StreamPtr will be null if
	inBitStreams has size 0 or if the StreamFormatter has not been set..
	*/
	template<class T>
	Stream<T> popStream();

	//Returns the instance of RakPeer 
	RakNet::RakPeerInterface* getRakPeerInstance() const;

private:

	//pointer to the server instance of RakPeerInterface
	RakNet::RakPeerInterface* RakPeerInstance;
	//pointer to the formatter used to format BitStreams into Streams
	XLib::SharedPtr<StreamFormatter> formatter;
	XLib::Vector<XLib::SharedPtr<RakNet::BitStream>> inBitStreams;
};

template<class T>
XLib::Vector<Stream<T>> NetworkComponent::getStreams() const {
	XLib::Vector<Stream<T>> ret;
	if (formatter) {
		for (auto iter = inBitStreams.begin(), iter != inBitStreams.end(); iter++) {
#ifdef SERVER
			ret.push_back(Stream<T>(*iter, formatter));
#endif /* SERVER */
#ifdef CLIENT
			ret.Add(Stream<T>(*iter, formatter));
#endif /* CLIENT */
		}
	}
	return ret;
}

template<class T>
Stream<T> NetworkComponent::popStream() {
	if (formatter)
		return Stream<T>(popBitStream(), formatter);
	else
		return Stream<T>();
}

#endif