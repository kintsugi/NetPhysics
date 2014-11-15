#ifdef CLIENT
	#include "NetPhysicsClient.h"
#endif
#include "Messenger.h"
#include "HandleManager.h"

Messenger::Messenger(HandleManager &handleManager) {
	handle = handleManager.add(this, MESSENGER);
}

void Messenger::postMessage(HandleManager &handleManager, Message* msg)  {
#ifdef SERVER
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
#endif /* SERVER */
}

void Messenger::receiveMessage(Message* msg) {
#ifdef SERVER
	inbox.push_back(msg);
#endif /* SERVER */
}

XLib::Vector<Message*> Messenger::getInbox() {
#ifdef SERVER
	XLib::Vector<Message*> ret = inbox;
	inbox.clear();
	return ret;
#endif /* SERVER */
}

void Messenger::subscribe(Handle messengerHandle, const int messageType) {
#ifdef SERVER
	subscribers.insert(std::make_pair(messageType, Subscriber(messengerHandle)));
#endif /* SERVER */
}

Handle Messenger::getHandle() const {
	return handle;
}