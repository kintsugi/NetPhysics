#include "SpaceFighter_client.h"
#include "messenger.h"
#include "handlemanager.h"

Messenger::Messenger(HandleManager* handleManager) {
	handle = handleManager->add(this, MESSENGER);
}

void Messenger::postMessage(HandleManager* handleManager, Message* msg) {
	for (auto iter = subscribers.CreateKeyIterator(msg->type); iter; iter.operator++()) {
		Subscriber *subscriber = &iter.Value();
		Messenger* recipient = (Messenger*)handleManager->get(subscriber->getSubscriberHandle());
		if (recipient != NULL)
			recipient->receiveMessage(msg);
		else
			iter.RemoveCurrent();
	}
}

void Messenger::receiveMessage(Message* msg) {
	inbox.Add(msg);
}

TArray<Message*> Messenger::getInbox() {
	TArray<Message*> ret = inbox;
	inbox.Reset();
	return ret;
}

void Messenger::subscribe(Handle messengerHandle, const int messageType) {
	subscribers.Add(messageType, Subscriber(messengerHandle));
}

Handle Messenger::getHandle() const{
	return handle;
}