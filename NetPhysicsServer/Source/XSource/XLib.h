#ifdef NET_PHYSICS_SERVER
#ifndef X_LIB_H_INCLUDED
#define X_LIB_H_INCLUDED

#include <vector>
#include <memory>
#include <unordered_map>
#include <stdint.h>

namespace NetPhysics {
	namespace XLib {
		template <typename T>
		struct Vector {
			typedef typename std::vector<T>::iterator iterator;
			typedef typename std::vector<T>::const_iterator const_iterator;
			Vector<T>& operator=(const Vector<T> &comp) {
				if (this != &comp)
					container = comp.container;
				return *this;
			}
			T& operator[](std::size_t pos) { return container[pos]; }
			const T& operator[](std::size_t pos) const {
				return const_cast<T&>(container[pos]);
			}
			T& front() { return container.front(); }
			const T& front() const { return container.front(); }
			T& back() { return container.back(); }
			const T& back() const { return container.back(); }
			T* data() { return data(); }
			iterator begin() { return container.begin(); }
			const_iterator cbegin() {
				return container.cbegin();
			}
			iterator end() { return container.end(); }
			const_iterator cend() { return container.cend(); }
			bool empty() const { return container.empty(); }
			std::size_t size() const { return container.size(); }
			std::size_t max_size() const { return container.max_size(); }
			void reserve(std::size_t new_cap) { container.reserve(new_cap); }
			std::size_t capacity() const { return container.capacity(); }
			void shrink_to_fit() { container.shrink_to_fit(); }
			void clear() { container.clear(); }
			iterator insert(iterator pos, const T& value) {
				return container.insert(pos, value);
			}
			iterator insert(const_iterator pos, const T& value)
			{
				return container.insert(pos, value);
			}
			iterator insert(const_iterator pos, T&& value) {
				return container.insert(pos, value);
			}
			void insert(iterator pos, std::size_t count, const T& value) {
				container.insert(pos, count, value);
			}
			iterator insert(const_iterator pos, std::size_t count, const T& value) {
				return container.insert(pos, count, value); 
			}
			iterator erase(iterator pos) { return container.erase(pos); }
			iterator erase(const_iterator pos) { return container.erase(pos); }
			iterator erase(iterator first, iterator last) {
				return container.erase(first, last);
			}
			iterator erase(const_iterator first, const_iterator last) {
				return container.erase(first, last);
			}
			void push_back(const T& value) { container.push_back(value); }
			void push_back(T&& value) { container.push_back(value); }
			void pop_back() { container.pop_back(); }
			void resize(std::size_t count) { container.resize(count); }
			void resize(std::size_t count, const T& value) {
				container.resize(count, value);
			}
			std::vector<T> container;
		};

		template <typename S, typename T>
		struct UnorderedMap {
			typedef typename std::unordered_map<S, T>::iterator iterator;
			typedef typename std::unordered_map<S, T>::const_iterator const_iterator;

			UnorderedMap<S, T>& operator=(const UnorderedMap<S, T> &comp) {
				if (this != &comp)
					container = comp.container;
				return *this;
			}
			iterator begin() { return container.begin(); }
			const_iterator cbegin() { return container.cbegin(); }
			iterator end() { return container.end(); }
			const_iterator cend() { return container.cend(); }
			bool empty() const { return container.empty(); }
			std::size_t size() const { return container.size(); }
			std::size_t max_size() const { return container.max_size(); }
			void clear() { container.clear(); }
			iterator insert(const S &key, const T &value) {
				std::pair<iterator, bool> ret = container.insert(
					std::make_pair(key, value));
				return ret.first;
			}
			iterator erase(const_iterator pos){ return container.erase(pos); }
			iterator erase(const_iterator first, const_iterator last) {
				return container.erase(first, last);
			}
			std::size_t erase(const S& key) { return container.erase(key); }
			T& operator[](const S &key) { return container[key]; }
			T& operator[](S &&key) { return container[key]; }
			std::size_t count(const S& key) const { return container.count(key); }
			T* find(const S& key) {
				auto got = container.find(key);
				return &got->second;
			}
			const T* find(const S& key) const {
				auto got = container.find(key);
				return &got->second;
			}
			std::unordered_map<S, T> container;
		};

		template <typename S, typename T>
		struct UnorderedMultiMap {
			typedef typename std::unordered_multimap<S, T>::iterator iterator;
			typedef typename std::unordered_multimap<S, T>::const_iterator const_iterator;
			UnorderedMultiMap<S, T>& operator=(const UnorderedMap<S, T> &comp) {
				if (this != &comp)
					container = comp.container;
				return *this;
			}
			iterator begin() { return container.begin(); }
			const_iterator cbegin() { return container.cbegin(); }
			iterator end() { return container.end(); }
			const_iterator cend() { return container.cend(); }
			bool empty() const { return container.empty(); }
			int32_t size() const { return container.size(); }
			int32_t max_size() const { return container.max_size(); }
			void clear() { container.clear(); }
			iterator insert(const S &key, const T &value) {
				return container.insert(std::make_pair(key, value));
			}
			iterator erase(const_iterator pos){ return container.erase(pos); }
			iterator erase(const_iterator first, const_iterator last) {
				return container.erase(first, last);
			}
			int32_t erase(const S &key) { return container.erase(key); }
			int32_t count(const S &key) const { return container.count(key); }
			Vector<T*> find(const S &key) {
				std::size_t bucket = container.bucket(key);
				Vector<T*> ret;
				for (auto iter = container.begin(bucket); iter != container.end(bucket); ++iter)
					ret.push_back(&*iter);
				return ret;
			}
			Vector<const T*> find(const S &key) const {
				std::size_t bucket = container.bucket(key);
				Vector<const T*> ret;
				for (auto iter = container.cbegin(bucket); iter != container.cend(bucket); ++iter)
					ret.push_back(const_cast<T*>(&*iter));
				return ret;
			}
			std::unordered_multimap<S, T> container;
		};

		template<typename T> using SharedPtr = std::shared_ptr<T>;
		using String = std::string;

		
	}
}

#endif /* X_LIB_H_INCLUDED */
#endif /* NET_PHYSICS_SERVER */

#ifdef NET_PHYSICS_CLIENT
#pragma once
#include "NetPhysicsClient.h"
namespace NetPhysics {
	namespace XLib {
		template<typename T>
		struct Vector {
			typedef typename TArray<T>::TIterator iterator;
			typedef typename TArray<T>::TConstIterator const_iterator;
			Vector<T>& operator=(const Vector<T> &comp) {
				if (this != &comp)
					container = comp.container;
				return *this;
			}
			T& operator[](int32_t pos) { return container[pos]; }
			const T& operator[](int32_t pos) const {
				return container[pos];
			}
			T& front() { return container[0]; }
			const T& front() const { return container[0]; }
			T& back() { return container.Last(); }
			const T& back() const { return container[container.Num() - 1]; }
			T* data() { return GetData(); }
			iterator begin() { return container.CreateIterator() }
			const_iterator cbegin() {
				return container.CreateConstIterator();
			}
			iterator end() { return begin + (size() - 1); }
			const_iterator cend() { return cbegin + (size() - 1); }
			bool empty() const { return size() == 0 ? true : false; }
			int32_t size() const { return container.Num(); }
			int32_t max_size() const { return container.Max(); }
			void reserve(int32_t new_cap) { container.Reserve(new_cap); }
			int32_t capacity() const { return container.GetAllocatedSize(); }
			void shrink_to_fit() { container.Shrink(); }
			void clear() { container.Empty(); }
			iterator insert(iterator pos, const T& value) {
				return begin() + container.Insert(value, pos.GetIndex());
			}
			iterator insert(const_iterator pos, const T& value)
			{
				return begin() + container.Insert(value, pos.GetIndex());
			}
			iterator insert(const_iterator pos, T&& value) {
				return begin() + container.Insert(value, pos.GetIndex());
			}
			void insert(iterator pos, int32_t count, const T& value) {
				TArray<T> values; values.Init(value, count);
				container.Insert(values, pos.GetIndex());
			}
			iterator insert(const_iterator pos, int32_t count, const T& value) {
				TArray<T> values; values.Init(value, count);
				return begin() + container.Insert(values, pos.GetIndex());
			}
			iterator erase(iterator pos) {
				container.RemoveAt(pos.GetIndex());
				return begin() + pos.GetIndex() != end() ? begin() + pos.GetIndex() : end();
			}
			iterator erase(const_iterator pos) {
				container.RemoveAt(pos.GetIndex());
				return begin() + pos.GetIndex() != end() ? begin() + pos.GetIndex() : end();
			}
			iterator erase(iterator first, iterator last) {
				if (first < last) {
					int32_t count = (last.GetIndex() - first.GetIndex()) + 1;
					container.RemoveAt(first.GetIndex(), count);
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				} else if (first > last) {
					int32_t count = (first.GetIndex() - last.GetIndex()) + 1;
					container.RemoveAt(last.GetIndex(), count);
					return begin() + last.GetIndex() < end() ? begin() + last.GetIndex() : end();
				} else {
					erase(first);
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				}
				
			}
			iterator erase(const_iterator first, const_iterator last) {
				if (first < last) {
					int32_t count = (last.GetIndex() - first.GetIndex()) + 1;
					container.RemoveAt(first.GetIndex(), count);
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				} else if (first > last) {
					int32_t count = (first.GetIndex() - last.GetIndex()) + 1;
					container.RemoveAt(last.GetIndex(), count);
					return begin() + last < end() ? begin() + last.GetIndex() : end();
				} else {
					erase(first);
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				}
			}
			void push_back(const T& value) { container.Add(value); }
			void push_back(T&& value) { container.Add(value); }
			void pop_back() { container.Pop(); }
			void resize(int32_t count) { container.Reserve(count); }
			void resize(int32_t count, const T& value) {
				if (count > size()) {
					numAppend = count - size();
					container.Reserve(count);
					for (uint32 i = numAppend; i != 0; --i) {
						container[size() - 1 - i] = value;
					}
				} else
					container.Reserve(count);
			}
			TArray<T> container;
		};

		template <typename S, typename T>
		struct UnorderedMap {
			typedef typename TMapBase<S, T, false>::TIterator iterator;
			typedef typename TMapBase<S, T, false>::TConstIterator const_iterator;

			UnorderedMap<S, T>& operator=(const UnorderedMap<S, T> &comp) {
				if (this != &comp)
					container = comp.container;
				return *this;
			}
			iterator begin() { return container.CreateIterator() }
			const_iterator cbegin() {
				return container.CreateConstIterator();
			}
			iterator end() { return begin + (size() - 1); }
			const_iterator cend() { return cbegin + (size() - 1); }
			bool empty() const { return size() == 0 ? true : false; }
			int32_t size() const { return container.Num(); }
			int32_t max_size() const { return container.Max(); }
			void clear() { container.Empty(); }
			iterator insert(const S &key, const T &value) {
				container.Add(key, value);
				iterator ret = container.CreateKeyIterator(key);
				return begin() + ret.GetIndex();
			}
			iterator erase(iterator pos){
				pos.RemoveCurrent();
				return begin() + (pos.GetIndex() - 1);
			}
			iterator erase(iterator first, iterator last) {
				if (first < last) {
					auto ret = first;
					while (first <= last) {
						first.RemoveCurrent();
						++first;
					}
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				} else if (first > last) {
					auto ret = last - 1;
					while (last <= first) {
						last.RemoveCurrent();
						++last;
					}
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				} else {
					first.RemoveCurrent();
					return return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				}
			}
			int32_t erase(const S& key) { return container.Remove(key); }
			T& operator[](const S &key) { return container[key]; }
			T& operator[](S &&key) { return container[key]; }
			int32_t count(const S& key) const { return container.GetKeys(key); }
			T* find(const S& key) {
				return &*container.CreateKeyIterator(key);
			}
			const T* find(const S& key) const {
				return &*container.CreateConstKeyIterator(key);
			}
			TMapBase<S, T, false> container;
		};

		template <typename S, typename T>
		struct UnorderedMultiMap {
			typedef typename TMultiMap<S, T>::TIterator iterator;
			typedef typename TMultiMap<S, T>::TConstIterator const_iterator;
			UnorderedMultiMap<S, T>& operator=(const UnorderedMap<S, T> &comp) {
				if (this != &comp)
					container = comp.container;
				return *this;
			}
			iterator begin() { return container.CreateIterator() }
			const_iterator cbegin() {
				return container.CreateConstIterator();
			}
			iterator end() { return begin + (size() - 1); }
			const_iterator cend() { return cbegin + (size() - 1); }
			bool empty() const { return size() == 0 ? true : false; }
			int32_t size() const { return container.Num(); }
			int32_t max_size() const { return container.Max(); }
			void clear() { container.Empty(); }
			iterator insert(const S &key, const T &value) {
				container.Add(key, value);
				iterator ret = container.CreateKeyIterator(key);
				return begin() + ret.GetIndex();
			}
			iterator erase(iterator pos){
				pos.RemoveCurrent();
				return begin() + (pos.GetIndex() - 1);
			}
			iterator erase(iterator first, iterator last) {
				if (first < last) {
					auto ret = first;
					while (first <= last) {
						first.RemoveCurrent();
						++first;
					}
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				} else if (first > last) {
					auto ret = last - 1;
					while (last <= first) {
						last.RemoveCurrent();
						++last;
					}
					return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				} else {
					first.RemoveCurrent();
					return return begin() + first.GetIndex() < end() ? begin() + first.GetIndex() : end();
				}
			}
			int32_t erase(const S& key) { return container.Remove(key); }
			int32_t count(const S& key) const { return container.GetKeys(key); }
			Vector<T*> find(const S &key) {
				Vector<T*> ret;
				for (auto iter = container.CreateKeyIterator(key); iter; iter++)
					ret.push_back(&*iter);
				return ret;
			}
			Vector<const T*> find(const S &key) const {
				Vector<const T*> ret;
				for (auto iter = container.CreateKeyIterator(key); iter; iter++)
					ret.push_back(const_cast<T*>(&*iter));
				return ret;
			}

			TMultiMap<S, T> container;
		};

		template <class T> using SharedPtr = TSharedPtr<T>;
		using String = FString;
	}
}
#endif /* NET_PHYSICS_CLIENT */