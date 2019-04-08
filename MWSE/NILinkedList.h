#pragma once

#include "NIDefines.h"

namespace NI {
	template <typename T>
	struct LinkedList {
		T * data;
		LinkedList<T> * next;
	};
	static_assert(sizeof(LinkedList<void>) == 0x8, "NI::LinkedList failed size validation");

	typedef LinkedList<DynamicEffect> DynamicEffectLinkedList;
	typedef LinkedList<Node> NodeLinkedList;
	typedef LinkedList<Property> PropertyLinkedList;
}
