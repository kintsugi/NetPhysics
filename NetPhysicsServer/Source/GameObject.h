#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include <string>
#include "XLib.h"
#include "ComponentHandle.h"
#include "GameObjectFilter.h"
#include "Messenger.h"

/*
	GameObject class encapsulates handles to components.
	Access added components by using HandleManager::Get
	Handle::type denotes the type of the component.
	A GameObject cannot have multiple of the same component, or things get weird.
*/
class GameObject {

public:
	GameObject(HandleManager& handleManager);

	/*
	Adds the component that Handle points to to the game object.
	@param handle the handle of the components
	*/
	bool addComponent(HandleManager &handleManager, const ComponentHandle componentHandle);

	//TODO comment
	template<class T>
	T* getComponent(HandleManager &handleManager, const ComponentType type);

	void removeComponent(HandleManager &handleManager, ComponentType type);

	bool hasComponent(ComponentType type);
	bool hasComponents(GameObjectFilter filter);

	/*
	Remove the handle of the object and all handles of its component from the handle manager
	Note: when a GameObject of component does not have a valid handle, its manager deletes it next update.
	All subsequent calls to the data the handle pointed to will be null
	*/
	void destroy(HandleManager &handleManager);

	//Returns the handle of the object
	Handle getHandle() const;
	std::string getTag();
	void setTag(std::string newTag);
	Messenger* getMessenger();
private:
	Handle handle;
	Messenger messenger;
	std::string tag;
	XLib::UnorderedMap<ComponentType, ComponentHandle> components;
	XLib::Vector<Handle> children;
	
};

template<class T>
T* GameObject::getComponent(HandleManager &handleManager, const ComponentType type) {
	auto got = components.find(type);
	if (got != components.end()) {
		return (T*)handleManager.get(got->second);
	}
	return NULL;
}

#endif