package elements_of_prog_interviews_in_java.common;

import java.util.HashMap;

import elements_of_prog_interviews_in_java.common.DoublyLinkedList.DoublyLinkedListNode;

public class LRU<T> {
	DoublyLinkedList<T> recent;
	HashMap<T, DoublyLinkedListNode<T>> cacheMap;
	int cacheSize;

	public LRU(int cacheSize) {
		this.cacheSize = cacheSize;
		recent = new DoublyLinkedList<T>();
		cacheMap = new HashMap<T, DoublyLinkedListNode<T>>();
	}

	public T get(T key) {
		DoublyLinkedListNode<T> cached = cacheMap.get(key);
		if (cached != null) {
			recent.remove(cached);
			recent.append(cached);
			return cached.data;
		}
		return null;
	}

	public void put(T key) {
		DoublyLinkedListNode<T> cached = cacheMap.get(key);
		if (cached != null) {
			recent.remove(cached);
		}
		recent.append(cached);

		// Limit the size of the cache
		if (cacheMap.size() > cacheSize) {
			cacheMap.remove(recent.head.data);
			recent.remove(recent.head);
		}
	}
}
