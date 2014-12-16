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
		class Vector : public std::vector<T> {
		public:

			reference front_X() { return front(); }
			reference back_X() { return back(); }
			T* data_X() { return data(); }
			iterator begin_X() { return begin(); }
			iterator end_X() { return end(); }
			bool empty_X() { return empty(); }
			size_type size_X() const { return size(); }
			size_type max_size_X() const { return max_size(); }
			void reserve_X(size_type new_cap) { reserve(new_cap); }
			size_type capacity_X() const { return capacity(); }
			void shrink_to_fit_X() { shrink_to_fit(); }
			void clear_X() { clear(); }
			iterator insert_X(iterator pos, const T& value) { return insert(pos, value); }
			iterator erase_X(iterator pos) { return erase(pos); }
			iterator erase_X(iterator first, iterator last) { return erase(first, last); }
			void push_back_X(const T& value) { push_back(value); }
			void push_back_X(T&& value) { push_back(value); }
			void pop_back_X() { pop_back(); }
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