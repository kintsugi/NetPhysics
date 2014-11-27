#ifdef NET_PHYSICS_SERVER
#ifndef X_LIB_H_INCLUDED
#define X_LIB_H_INCLUDED

#include <vector>
#include <memory>
#include <unordered_map>

namespace NetPhysics {
	namespace XLib {
		template <class T> using Vector = std::vector<T>;
		template <class T> using SharedPtr = std::shared_ptr<T>;
		template <class S, class T> using UnorderedMap = std::unordered_map<S, T>;
		template <class S, class T> using UnorderedMultiMap = std::unordered_multimap<S, T>;
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
		template <class T> using Vector = TArray<T>;
		template <class T> using SharedPtr = TSharedPtr <T>;
		template <class S, class T> using UnorderedMap = TMap <S, T>;
		template <class S, class T> using UnorderedMultiMap = TMultiMap <S, T>;
		using String = FString;
	}
}
#endif /* NET_PHYSICS_CLIENT */