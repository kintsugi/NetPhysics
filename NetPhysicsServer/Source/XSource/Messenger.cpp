#ifdef NET_PHYSICS_CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "Messenger.h"
#include "HandleManager.h"

using namespace NetPhysics;

Messenger::Messenger(HandleManager &handleManager)
	: handle(handleManager.add(this, MESSENGER))
{}

void Messenger::postMessage(HandleManager &handleManager, Message* msg) {
	auto range = subscribers.find(msg->type);
	for (auto iter = range.begin(); iter != range.end(); iter++) {
		Messenger* subscriber = (Messenger*)handleManager.get((*iter)->getSubscriberHandle());
		if (subscriber != nullptr)
			subscriber->receiveMessage(msg);
		else {
#ifdef NET_PHYSICS_SERVER
			iter = range.erase(iter);
#endif /* NET_PHYSICS_SERVER */
#ifdef NET_PHYSICS_CLIENT
			range.erase(iter);
			iter--;
#endif /* NET_PHYSICS_CLIENT */
			subscribers.erase(msg->type);
		}
	}
}

void Messenger::receiveMessage(Message* msg) {
	inbox.push_back(msg);
}

XLib::Vector<Message*> Messenger::getInbox() {
	XLib::Vector<Message*> ret = inbox;
	inbox.clear();
	return ret;
}

void Messenger::subscribe(Handle messengerHandle, const uint32_t messageType) {
	subscribers.insert(messageType, Subscriber(messengerHandle));
}

Handle Messenger::getHandle() const {
	return handle;
}