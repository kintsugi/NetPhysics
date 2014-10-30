#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#include <vector>
#include <memory>
#include "NetworkIDObject.h"
#include "BitStream.h"
#include "stream.h"
#include "handle.h"

class HandleManager;

/*
	Class for handling inbound and outbound data for an entity between the client and the server.
	Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent : public RakNet::NetworkIDObject {
public:

	/*
	@param handleManager reference to a handleManager to manage this object
	@param peer pointer to the server instance of RakNet
	@param manager pointer to a NetworkIDManager object for this object
	*/
	NetworkComponent(HandleManager& handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer);

	/*
	@param handleManager reference to a handleManager to manage this object
	@param peer pointer to the server instance of RakNet
	@param manager pointer to a NetworkIDManager object for this object
	@param formatter virtual class that determines how to format BitStreams. Uses default if NULL
	*/
	NetworkComponent(HandleManager& handleManager, RakNet::NetworkIDManager &networkIDManager, RakNet::RakPeerInterface* peer, StreamFormatter* newFormatter);

	/*
	Sets the formatter the object uses to format BitStreams.
	@param newFormatter pointer to either a StreamFormatter base or abstract class
	*/
	void setFormatter(StreamFormatter* newFormatter);

	/*
	Takes a BitStream, formats it with the StreamFormatter and adds it to member streams
	@param inBS the BitStream to add.
	*/
	void addBitStream(std::shared_ptr<RakNet::BitStream> inBS);
	
	//returns the streams container.
	std::vector<Stream> getAllStreams() const;

	//Returns all streams of StreamType type. Can use an int.
	std::vector<Stream> getStreamsOfType(StreamType type);

	//Clears the streams container
	void removeAllStreams();

	//Erases all streams of StreamType type. Can use an int.
	void removeStreamsOfType(StreamType type);
	
	//Returns the instance of RakPeer 
	RakNet::RakPeerInterface* getRakPeerInstance() const;

	//Returns the handle of this object.
	Handle getHandle() const;

private:
	//The handle of this object.
	Handle handle;
	//pointer to the server instance of RakPeerInterface
	RakNet::RakPeerInterface* RakPeerInstance;
	//pointer to the formatter used to format BitStreams into Streams
	StreamFormatter* formatter;
	//Container of received Stream objects.
	std::vector<Stream> streams;
};


#endif