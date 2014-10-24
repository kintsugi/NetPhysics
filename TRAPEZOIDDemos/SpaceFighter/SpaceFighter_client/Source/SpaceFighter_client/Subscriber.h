#pragma once

#include "SpaceFighter_client.h"
#include "handle.h"

class Subscriber {
public:
	//Maybe change to function and handle manager?
	Subscriber(const Handle newSubscriberHandle) : subscriberHandle(newSubscriberHandle) {}
	Handle getSubscriberHandle() const { return subscriberHandle; }

private:
	//Handle to the messenger that receives the messages of the owning messenger.
	Handle subscriberHandle;
};