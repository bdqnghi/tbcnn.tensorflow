package lru;

import java.util.HashMap;

public class LruCache {

	private int capacity;
	private HashMap<Integer, Node> lruCache;
	private Node head;
	private Node tail;
	
	public LruCache(int size) {
		this.capacity = size;
		lruCache = new HashMap<Integer, Node>();
	}
	
	public class Node {
		private int value;
		private Node pre;
		private Node next;
		
		public Node(int value) {
			this.value = value;
		}
	}
	
	public void insertHeadNode(Node node) {
		if (head != null) {
			head.pre = node;
			node.next = head;
		}
		head = node;
		
		if (tail == null) {
			tail = head;
		}
	}
	
	public void removeNode(Node node) {
		if (node.pre == null) {
			head = node.next;
		} else {
			node.pre.next = node.next;
		}
		
		if (node.next == null) {
			tail = node.pre;
		} else {
			node.next.pre = node.pre;
		}
	}
	
	public void put(int key) {
		Node node = lruCache.get(key);
		if (lruCache.containsKey(key)) {
			removeNode(node);
			insertHeadNode(node);
		} else {
			if (lruCache.size() >= capacity) {
				removeNode(tail);
				lruCache.remove(key);
			}
			Node newNode = new Node(key);
			insertHeadNode(newNode);
			lruCache.put(key, newNode);
		}
	}
	
	public Integer get(int key) {
		if (lruCache.containsKey(key)) {
			Node node = lruCache.get(key);
			removeNode(node);
			insertHeadNode(node);
			return key;
		}
		return null;
	}
	
	public void printLru() {
		Node node = head;
		while(node != null) {
			System.out.println(node.value);
			node = node.next;
		}
		System.out.println("------------");
	}
	
	public static void main(String[] args) {
		LruCache lruCache = new LruCache(3);
		
		lruCache.put(3);
		lruCache.printLru();
		lruCache.put(6);
		lruCache.printLru();
		lruCache.put(9);
		lruCache.printLru();
		lruCache.put(7);
		lruCache.printLru();
		lruCache.put(9);
		lruCache.printLru();
		lruCache.put(2);
		lruCache.printLru();
	}
}
