#ifndef NETWORK_COMPONENT_H_INCLUDED
#define NETWORK_COMPONENT_H_INCLUDED

#include <vector>
#include <memory>
#include "BitStream.h"
#include "stream.h"
#include "handle.h"

class HandleManager;

/*
	Class for handling inbound and outbound data for an entity between the client and the server.
	Network Components made with new have to be deleted manually in the composing entity.
*/
class NetworkComponent {
public:
	/*
	@param peer pointer to the server instance of RakNet
	@param manager pointer to a NetworkIDManager object for this object
	@param formatter virtual class that determines how to format BitStreams. Uses default if NULL
	*/
	NetworkComponent(HandleManager& handleManager, RakNet::RakPeerInterface* peer);
	NetworkComponent(HandleManager& handleManager, RakNet::RakPeerInterface* peer, StreamFormatter* formatter);

	/*
	Sets the formatter the object uses to format BitStreams.
	@param formatter pointer to either a StreamFormatter base or abstract class
	*/
	void setFormatter(StreamFormatter* formatter);

	/*
	Takes a BitStream, formats it with the StreamFormatter and adds it to the streams container
	@param inBS the BitStream to add.
	*/
	void addBitStream(std::shared_ptr<RakNet::BitStream> inBS);

	
	//returns the streams container.
	std::vector<Stream> getAllStreams();

	//Returns all streams of StreamType type. Can use an int.
	std::vector<Stream> getStreamsOfType(StreamType type);

	//Clears the streams container
	void removeAllStreams();

	//Erases all streams of StreamType type. Can use an int.
	void removeStreamsOfType(StreamType type);
	
	//Returns the instance of RakPeer 
	RakNet::RakPeerInterface* getRakPeerInstance();

	Handle getHandle();
private:
	Handle handle;
	RakNet::RakPeerInterface* RakPeerInstance;
	StreamFormatter* formatter;
	std::vector<Stream> streams;
};


#endif