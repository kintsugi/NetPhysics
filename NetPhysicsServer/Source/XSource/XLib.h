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
			std::vector<T>::iterator begin() { return container.begin(); }
			std::vector<T>::const_iterator cbegin() {
				return container.cbegin();
			}
			std::vector<T>::iterator end() { return container.end(); }
			std::vector<T>::const_iterator cend() { return container.cend(); }
			bool empty() const { return container.empty(); }
			size_type size() const { return container.size(); }
			size_type max_size() const { return container.max_size(); }
			void reserve_X(size_type new_cap) { reserve(new_cap); }
			size_type capacity() const { return container.capacity(); }
			void shrink_to_fit() { container.shrink_to_fit(); }
			void clear() { container.clear(); }
			std::vector<T>::iterator insert(
				std::vector<T>::iterator pos,
				const T& value)
			{
				return container.insert(pos, value);
			}
			std::vector<T>::iterator insert(
				std::vector<T>::const_iterator pos,
				const T& value)
			{
				return container.insert(pos, value);
			}
			std::vector<T>::iterator insert(
				std::vector<T>::const_iterator pos,
				T&& value)
			{
				return container.insert(pos, value);
			}
			void insert(
				std::vector<T>::iterator pos,
				size_type count,
				const T& value)
			{
				container.insert(pos, count, value);
			}
			std::vector<T>::iterator insert(
				std::vector<T>::const_iterator pos,
				size_type count,
				const T& value) 
			{
				return container.insert(pos, count, value); 
			
			}
			std::vector<T>::iterator erase(std::vector<T>::iterator pos) {
				container.erase(pos);
			}
			std::vector<T>::iterator erase(std::vector<T>::const_iterator pos) {
				container.erase(pos);
			}
			std::vector<T>::iterator erase(
				std::vector<T>::iterator first,
				std::vector<T>::iterator last)
			{
				container.erase(first, last);
			}
			std::vector<T>::iterator erase(
				std::vector<T>::const_iterator first,
				std::vector<T>::const_iterator last)
			{
				container.erase(first, last);
			}
			void push_back(const T& value) { container.push_back(value); }
			void push_back(T&& value) { container.push_back(value); }
			void pop_back() { container.pop_back(); }
			std::vector<T> container;
		};

		
		template <class S, class T>
		class UnorderedMap : public std::unordered_map <S, T> {
		public:

			iterator begin_X() { return begin(); }
			iterator end_X() { return end(); }
			bool empty_X() { return empty(); }
			size_type size_X() const { return size(); }
			size_type max_size_X() const { return max_size(); }
			void clear_X() { clear(); }
			void insert_X(S& key, T& value) { insert(std::make_pair(key, value)); }
			iterator erase_X(const_iterator pos) { erase(pos); }
			size_type erase_X(const S& key) { erase(key); }
			iterator find_X(const S& key) { return find(key); }
			T& get_X(const S& key) { return find(key)->value_type->second; }
		};
		template <class S, class T>
		class UnorderedMultiMap : public std::unordered_multimap < S, T > {

			iterator begin_X() { return begin(); }
			iterator end_X() { return end(); }
			bool empty_X() { return empty(); }
			size_type size_X() const { return size(); }
			size_type max_size_X() const { return max_size(); }
			void clear_X() { clear(); }
			void insert_X(S& key, T& value) { insert(std::make_pair(key, value)); }
			iterator erase_X(const_iterator pos) { erase(pos); }
			size_type erase_X(const S& key) { erase(key); }
			iterator find_X(const S& key) { return find(key); }
		};

		template <class T> using SharedPtr = std::shared_ptr<T>;
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

		template <class T>
		class Vector : public TArray<T> {
		public:

			ElementType& front_X() { return Last(Num() - 1); }
			T& back_X() { return Last(); }
			ElementType* data_X() { return GetData(); }
			TIterator begin_X() { return CreateIterator(); }
			TIterator end_X() { return CreateIterator() + (Num() - 1); }
			bool empty_X() { return Num() == 0 ? true : false; }
			int32 size_X() { return Num(); }
			int32 max_size_X() { return Max(); }
			void reserve_X(int32 new_cap) { Reserve(new_cap); }
			uint32 capacity_X() { return GetAllocatedSize(); }
			void shrink_to_fit_X() { Shrink(); }
			void clear_X() { Empty(); }
			TIterator insert_X(TIterator pos, const ElementType &value) { return CreateIterator() + Insert(pos.GetIndex(), value); }
			TIterator erase_X(TIterator pos) {
				RemoveAt(pos.GetIndex());
				return pos--;
			}
			TIterator erase_X(TIterator first, TIterator last) {
				int32 count = last.GetIndex() - first.GetIndex();
				RemoveAt(first, count);
				return first--;
			}
			void push_back_X(const ElementType& value) { Add(value); }
			void push_back_X(T&& value) { Add(value); }
			void pop_back_X() { Pop(); }
		};

		template <class S, class T>
		class UnorderedMap : public TMap<S, T> {
		public:
			
			TIterator begin_X() { return CreateIterator(); }
			TIterator end_X() { return CreateIterator() + (Num() - 1); }
			bool empty_X() { return Num() == 0 ? true : false; }
			int32 size_X() { return Num(); }
			int32 max_size_X() { return Max(); }
			void clear_X() { Empty(); }
			void insert_X(S& key, T& value) { Add(key, value); }
			int32 erase_X(const S& key) { Remove(key); }
			TKeyIterator find_X(const S& key) { return CreateKeyIterator(key); }
			T& get_X(const S& key) { return Find(key); }
		};

		template <class S, class T>
		class UnorderedMultiMap : public TMultiMap<S, T> {

			TIterator begin_X() { return CreateIterator(); }
			TIterator end_X() { return CreateIterator() + (Num() - 1); }
			bool empty_X() { return Num() == 0 ? true : false; }
			int32 size_X() { return Num(); }
			int32 max_size_X() { return Max(); }
			void clear_X() { Empty(); }
			void insert_X(S& key, T& value) { Add(key, value); }
			int32 erase_X(const S& key) { Remove(key); }
			TKeyIterator find_X(const S& key) { return CreateKeyIterator(key); }
			T& get_X(const S& key) { return Find(key); }
		};

		template <class T> using SharedPtr = TSharedPtr<T>;
		using String = FString;
	}
}
#endif /* NET_PHYSICS_CLIENT */