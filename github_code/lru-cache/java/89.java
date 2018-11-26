package onlinejudge;

import java.util.HashMap;

/**
 * Title: LRU Cache
 * 
 * URL: https://leetcode.com/problems/lru-cache/
 * 
 * URL: http://www.lintcode.com/en/problem/lru-cache/
 * 
 * Difficulty: Hard
 * 
 * Design and implement a data structure for Least Recently Used (LRU) cache. It
 * should support the following operations: get and set.
 * 
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1. set(key, value) - Set or insert the
 * value if the key is not already present. When the cache reached its capacity,
 * it should invalidate the least recently used item before inserting a new
 * item.
 * 
 * Tags: [Linked List], [Doubly Linked List], [Data Structure]
 * 
 * @author Dongye Meng
 *
 */
public class LRUCache {
	public class DLLNode {
		public DLLNode prev;
		public DLLNode next;
		int key;
		int value;

		public DLLNode(int k, int v) {
			this.key = k;
			this.value = v;
			this.prev = null;
			this.next = null;
		}
	}

	public class DoublyLinkedList {
		public DLLNode head;
		public DLLNode tail;

		public DoublyLinkedList() {
			head = null;
			tail = null;
		}

		public void remove(DLLNode n) {
			if (n == this.head) { // Head
				this.head = n.next;
			}
			else {
				n.prev.next = n.next;
			}

			if (n == this.tail) { // Tail
				this.tail = n.prev;
			}
			else {
				n.next.prev = n.prev;
			}
		}

		public void insertAtFirst(DLLNode n) {
			if (this.head == null) {
				n.next = null;
				this.head = n;
				this.tail = n;
				n.prev = null;
			}
			else {
				n.next = this.head;
				this.head.prev = n;
				this.head = n;
				n.prev = null;
			}
		}
	}

	private int capacity;
	private HashMap<Integer, DLLNode> map;
	private DoublyLinkedList dList;

	public LRUCache(int capacity) {
		this.capacity = capacity;
		this.map = new HashMap<Integer, DLLNode>();
		this.dList = new DoublyLinkedList();
	}

	public int get(int key) {
		if (this.map.containsKey(key)) {
			DLLNode n = map.get(key);
			this.dList.remove(n);
			this.dList.insertAtFirst(n);
			return n.value;
		}
		else {
			return -1;
		}
	}

	public void set(int key, int value) {
		// The node exists
		if (this.map.containsKey(key)) {
			DLLNode n = this.map.get(key);
			n.value = value;
			this.dList.remove(n);
			this.dList.insertAtFirst(n);
		}
		// The node does not exist
		else {
			DLLNode n = new DLLNode(key, value);
			// Not full
			if (this.map.size() < this.capacity) {
				this.dList.insertAtFirst(n);
				this.map.put(key, n);
			}
			// Full
			else {
				this.dList.insertAtFirst(n);
				this.map.put(key, n);
				DLLNode deletedNode = this.dList.tail;
				this.dList.remove(deletedNode);
				this.map.remove(deletedNode.key);
			}
		}
	}
}
