#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include <unordered_map>
#include "handle.h"
#include "componenttypehandle.h"
#include "gameobjectfilter.h"
#include "messenger.h"


/*
	GameObject class encapulates handles to components.
	Access added components by using HandleManager::Get
	Handle::m_type denotes the type of the component.
	A gameobject cannot have multiple of the same component, or things get weird.
*/
class GameObject {
friend class GameObjectManager;
public:
	GameObject(HandleManager* handleManager);

	bool hasComponents(const GameObjectFilter filter) const;

	/*
	Adds the component that Handle points to to the game object
	@param handle the handle of the components
	@param type the type of component to be added
	*/
	bool addComponent(const Handle handle);

	ComponentTypeHandle* getComponentTypeHandle(const HandleType type);

	//TODO comment
	template<class T>
	T* getComponent(HandleManager *handleManager, const Handle handle);

	/*
	Returns a pointer to the handle of the component.
	@param handleManager the HandleManager containing the component
	@param type the type of component to be returned
	@return the pointer to the component. NULL if no component in this object
	*/
	template<class T>
	std::vector<T*> getComponents(HandleManager *handleManager, const HandleType type);
	
	bool removeComponent(HandleManager *handleManager, const Handle handle);

	/*
	Removes the components from the gameobject and the manager
	@param handleManager the HandleManager that contains the handle
	@param type the type of component to remove.
	*/
	bool removeComponents(HandleManager* handleManager, const HandleType type);

	/*
	Remove the handle of the object and all handles of its component from the handle manager
	Note: when a gameobject of component does not have a valid handle, its manager deletes it next update.
	All subsequent calls to the data the handle pointed to will be null
	*/
	void removeSelf(HandleManager *handleManager);

	//Sets the handle of the GameObject. Object must be created first before its handle is set.
	void setHandle(Handle handle);

	//Returns the handle of the object
	Handle getHandle() const;
	
	Messenger* getMessenger();
private:
	Handle handle;
	Messenger messenger;
	std::unordered_map<HandleType, ComponentTypeHandle> components;
	
};

template<class T>
T* GameObject::getComponent(HandleManager *handleManager, const Handle handle) {
	auto got = components.find(handle.type);
	if (got != components.end()) {
		int index = got->second.getHandleIndex(handle);
		if (index != -1)
			return (T*)handleManager->get(got->second.getHandles()[index]);
		else
			return NULL;
	}
	return NULL;
}

template<class T>
std::vector<T*> GameObject::getComponents(HandleManager *handleManager, const HandleType type) {
	std::vector<T*> ret;
	auto got = components.find(handle.type);
	if (got != components.end()) {
		std::vector<Handle> handles = got->second.getHandles();
		std::vector<T*> ret;
		for (auto iter = handles.begin; iter != handles.end(); iter++)
			ret.push_back((T*)handleManager->get(*iter));
	}
	return ret;
}




#endif