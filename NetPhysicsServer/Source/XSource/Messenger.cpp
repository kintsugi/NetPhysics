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
	auto range = subscribers.equal_range(msg->type);
	for (auto iter = range.first; iter != range.second; iter++) {
		Messenger* subscriber = (Messenger*)handleManager.get(iter->second.getSubscriberHandle());
		if (subscriber != nullptr)
			subscriber->receiveMessage(msg);
		else
			iter = subscribers.erase(iter);
	}
}

void Messenger::receiveMessage(Message* msg) {
	inbox.push_back(msg);
}

std::vector<Message*> Messenger::getInbox() {
	std::vector<Message*> ret = inbox;
	inbox.clear();
	return ret;
}

void Messenger::subscribe(Handle messengerHandle, const uint32_t messageType) {
	subscribers.insert(std::make_pair(messageType, Subscriber(messengerHandle)));
}

Handle Messenger::getHandle() const {
	return handle;
}