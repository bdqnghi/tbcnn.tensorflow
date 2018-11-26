/*
@Copyright:LintCode
@Author:   LLihao
@Problem:  http://www.lintcode.com/problem/lru-cache
@Language: Java
@Datetime: 17-06-01 22:55
*/

public class Solution {
    HashMap<Integer, Node> map;
	MyLinkedList ls;
	int capacity;

	// @param capacity, an integer
	public Solution(int capacity) {
		map = new HashMap<Integer, Node>(capacity);
		this.capacity = capacity;
		ls = new MyLinkedList();
	}

	// @return an integer
	public int get(int key) {
		if (map.containsKey(key)) {
			Node node = map.get(key);
			ls.removeNode(node);
			ls.appendNode(node);
			return node.val;
		}
		return -1;
	}

	// @param key, an integer
	// @param value, an integer
	// @return nothing
	public void set(int key, int value) {
		if (map.containsKey(key)) {
			Node node = map.get(key);
			ls.removeNode(node);
			ls.appendNode(node);
			node.val = value;
			return;
		}
		if (map.size() == capacity) {
			Node node = ls.dequeueNode();
			if (node != null) {
				map.remove(node.key);
			}
		}
		Node node = new Node(key, value);
		map.put(key, node);
		ls.appendNode(node);
	}

	class Node {
		Node prev;
		Node next;
		int val;
		int key;
		public Node(int key, int val) {
			this.key = key;
			this.val = val;
			prev = null;
			next = null;
		}
	}

	class MyLinkedList {
		Node head;
		Node tail;
		
		public MyLinkedList() {
			head = null;
			tail = null;
		}
		
		public void removeNode(Node node) {
			if (node.next != null) {
				node.next.prev = node.prev;
			}
			if (node.prev != null) {
				node.prev.next = node.next;
			}
			if (head == node) {
				head = node.next;
			}
			if (tail == node) {
				tail = node.prev;
			}
			node.prev = null;
			node.next = null;
		}
		
		public void appendNode(Node node) {
			if (head == null && tail == null) {
				head = node;
				tail = node;
			} else {
				tail.next = node;
				node.prev = tail;
				tail = node;
			}
		}
		
		public Node dequeueNode() {
			if (head != null) {
				Node node = head;
				head = head.next;
				node.next = null;
				return node;
			}
			return null;
		}
	}
}