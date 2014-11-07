#ifdef SERVER
#ifndef X_LIB_H_INCLUDED
#define X_LIB_H_INCLUDED

#include <vector>
#include <memory>
#include <unordered_map>

/*
	platform types between server and client shared code.
*/
namespace XLib {

	template <class T> using Vector = std::vector<T>;

	template <class T> using SharedPtr = std::shared_ptr<T>;

	template <class S, class T> using UnorderedMap = std::unordered_map<S, T>;

	template <class S, class T> using UnorderedMultiMap = std::unordered_multimap<S, T>;

}

#endif /* X_LIB_H_INCLUDED */
#endif /* SERVER */

#ifdef CLIENT

#pragma once
#include "SpaceFighter_client.h"

/*
	platform types between server and client shared code.
*/

namespace XLib {

	template <class T> using Vector = TArray<T>;

	template <class T> using SharedPtr = TSharedPtr <T>;

	template <class S, class T> using UnorderedMap = TMap <S, T>;

	template <class S, class T> using UnorderedMultiMap = TMultiMap <S, T>;
}

#endif /* CLIENT */