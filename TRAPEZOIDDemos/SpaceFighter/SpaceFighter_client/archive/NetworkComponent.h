#pragma once

#include "SpaceFighter_client.h"
#include "AllowWindowsPlatformTypes.h"
#include "BitStream.h"
#include "HideWindowsPlatformTypes.h"
#include "component.h"
#include "NetworkHandleObject.h"
#include "Stream.h"
#include "Handle.h"

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
	NetworkComponent(HandleManager& handleManager,
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
	void setFormatter(TSharedPtr<StreamFormatter> formatter);

	//Returns a pointer to the StreamFormatter of this object. NULL if it has not been set.
	TSharedPtr<StreamFormatter> getFormatter();

	/*
	Adds a BitStream to the container.
	@param inBS the BitStream to add.
	*/
	void addBitStream(TSharedPtr<RakNet::BitStream> inBS);

	//Returns the inBitStreams vector.
	TArray<TSharedPtr<RakNet::BitStream>> getBitStreams();

	//Returns the last index of the inBitStreams vector and removes it. NULL if empty. 
	TSharedPtr<RakNet::BitStream> popBitStream();

	//Clears the inBitStreams vector.
	void clearBitStreams();

	/*
	Returns a vector of Stream objects specialized to type T using the
	StreamFormatter object pointed to in member formatter. Has size 0 if
	inBitStreams has size 0 or if the StreamFormatter has not been set.
	*/
	template<class T>
	TArray<Stream<T>> getStreams();

	/*
	Returns a Stream object specialized to type T using the StreamFormatter
	object pointed to in member formatter. Uses the first index of the
	inBitStreams vector and removes it. Stream::StreamPtr will be null if
	inBitStreams has size 0 or if the StreamFormatter has not been set..
	*/
	template<class T>
	Stream<T> popStream();

	RakNet::RakPeerInterface* getRakPeerInstance() const;

private:

	RakNet::RakPeerInterface* RakPeerInstance;
	TSharedPtr<StreamFormatter> formatter;
	TArray<TSharedPtr<RakNet::BitStream>> inBitStreams;
};
