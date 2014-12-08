#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "Messenger.h"
#include "HandleManager.h"

using namespace NetPhysics;

Messenger::Messenger(HandleManager &handleManager) {
	handle = handleManager.add(this, MESSENGER);
}

void Messenger::postMessage(
	HandleManager &handleManager,
	Message* msg)
{
#ifdef NET_PHYSICS_SERVER
	auto range = subscribers.equal_range(msg->type);
	if (range.first != subscribers.end() && range.second != subscribers.end()) {
		for (auto iter = range.first; iter != range.second; iter++) {
			Messenger* subscriber = (Messenger*)handleManager.get(iter->second.getSubscriberHandle());
			if (subscriber != NULL)
				subscriber->receiveMessage(msg);
			else 
				iter = subscribers.erase(iter);
		}
	}
#endif /* NET_PHYSICS_SERVER */
}

void Messenger::receiveMessage(Message* msg) {
#ifdef NET_PHYSICS_SERVER
	inbox.push_back(msg);
#endif /* NET_PHYSICS_SERVER */
}

XLib::Vector<Message*> Messenger::getInbox() {
#ifdef NET_PHYSICS_SERVER
	XLib::Vector<Message*> ret = inbox;
	inbox.clear();
	return ret;
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
	XLib::Vector<Message*> ret = inbox;
	inbox.Reset();
	return ret;
#endif /* NET_PHYSICS_CLIENT */
}

void Messenger::subscribe(
	Handle messengerHandle,
	const int messageType)
{
#ifdef NET_PHYSICS_SERVER
	subscribers.insert(std::make_pair(messageType, Subscriber(messengerHandle)));
#endif /* NET_PHYSICS_SERVER */
}

Handle Messenger::getHandle() const {
	return handle;
}