#include "messenger.h"
#include "handlemanager.h"

Messenger::Messenger(HandleManager &handleManager) {
	handle = handleManager.add(this, MESSENGER);
}

void Messenger::postMessage(HandleManager &handleManager, Message* msg)  {
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
}

void Messenger::receiveMessage(Message* msg) {
	inbox.push_back(msg);
}

XLib::Vector<Message*> Messenger::getInbox() {
	XLib::Vector<Message*> ret = inbox;
	inbox.clear();
	return ret;
}

void Messenger::subscribe(Handle messengerHandle, const int messageType) {
	subscribers.insert(std::make_pair(messageType, Subscriber(messengerHandle)));
}

Handle Messenger::getHandle() const {
	return handle;
}