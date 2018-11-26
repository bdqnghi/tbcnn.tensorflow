package com.practice;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import com.practice.collection.DoublyLinkedList;
import com.practice.collection.DoublyLinkedList.Node;

public class LRU {

	int capacity;
	DoublyLinkedList cache = new DoublyLinkedList();
	Map<String, Node> refs = new HashMap<>();

	public LRU(int capacity) {
		this.capacity = capacity;
	}

	public int getVal(String key) {
		if (refs.containsKey(key)) {
			Node node = refs.get(key);
			cache.removeNode(node);
			cache.addFirst(node);
			return node.data;
		}
		return -1;
	}

	public void insert(String key, int data) {
		if (cache.getSize() == capacity) {
			Node removed = cache.removeLast();
			String leastUsed = null;
			for (Entry<String, Node> entry : refs.entrySet()) {
				if (entry.getValue() == removed) {
					leastUsed = entry.getKey();
				}
			}
			refs.remove(leastUsed);
		}
		Node node = new Node(data);
		cache.addFirst(node);
		refs.put(key, node);

	}
}
