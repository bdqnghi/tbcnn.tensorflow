package OJ0141_0150;

import java.util.Map;
import java.util.HashMap;
import java.util.LinkedHashMap;

public class LRU_Cache {
	/*
	 * https://leetcode.com/problems/lru-cache/discuss/45922/JAVA-Easy-Version-To-Understand!!!!
	 * 
	 * 1. The key to solve this problem is using a double linked list which enables 
	 *    us to quickly move nodes.
	 * 2. The LRU cache is a hash table of keys and double linked nodes. The hash 
	 *    table makes the time of get() to be O(1). The list of double linked nodes 
	 *    make the nodes adding/removal operations O(1).
	 *    
	 * Rf : https://leetcode.com/problems/lru-cache/discuss/45911/Java-Hashtable-+-Double-linked-list-(with-a-touch-of-pseudo-nodes)
	 */
	class Node {
		int key;
		int value;
		Node pre;
		Node next;

		public Node(int key, int value) {
			this.key = key;
			this.value = value;
		}
	}

	private HashMap<Integer, Node> map;
	private int capicity, count;
	private Node head, tail;

	public LRU_Cache(int capacity) {
		this.capicity = capacity;
		map = new HashMap<>();
		
		head = new Node(0, 0);
		tail = new Node(0, 0);
		head.next = tail;
		tail.pre = head;
		head.pre = null;
		tail.next = null;
		
		count = 0;
	}

	// Remove an existing node from the linked list.
	public void deleteNode(Node node) {
		node.pre.next = node.next;
		node.next.pre = node.pre;
	}

	// Always add the new node right after head;
	public void addToHead(Node node) {
		node.next = head.next;
		node.next.pre = node;
		node.pre = head;
		head.next = node;
	}
	
	// Move certain node in between to the head.
	public void moveToHead(Node node) {
		deleteNode(node);
		addToHead(node);
	}

	public int get(int key) {
		Node node = map.get(key);
		if (node == null) {
			return -1;
		}
		
		// move the accessed node to the head;
		moveToHead(node);
		
		return node.value;
	}

	public void put(int key, int value) {
		if (map.get(key) != null) {
			Node node = map.get(key);
			
			// update the value.
			node.value = value;
			moveToHead(node);
		} 
		else {
			Node node = new Node(key, value);
			map.put(key, node);
			
			if (count < capicity) {
				count++;
				addToHead(node);
			} 
			else {
				map.remove(tail.pre.key);
				deleteNode(tail.pre);
				addToHead(node);
			}
		}
	}
	
	/*
	 * The following are from this links.
	 * https://leetcode.com/problems/lru-cache/discuss/45939/Laziest-implementation:-Java's-LinkedHashMap-takes-care-of-everything
	 * 
	 * In the constructor, the third boolean parameter specifies the ordering mode. 
	 * If we set it to true, it will be in access order.
	 * https://docs.oracle.com/javase/8/docs/api/java/util/LinkedHashMap.html#LinkedHashMap-int-float-boolean-
	 * 
	 * By overriding removeEldestEntry in this way, we do not need to take care of it 
	 * ourselves. It will automatically remove the least recent one when the size of 
	 * map exceeds the specified capacity.
	 * https://docs.oracle.com/javase/8/docs/api/java/util/LinkedHashMap.html#removeEldestEntry-java.util.Map.Entry-
	 * 
	 * Rf : 
	 * leetcode.com/problems/lru-cache/discuss/45939/Laziest-implementation:-Java's-LinkedHashMap-takes-care-of-everything/112672
	 * leetcode.com/problems/lru-cache/discuss/45939/Laziest-implementation:-Java's-LinkedHashMap-takes-care-of-everything/45378
	 */
	class LRUCache {
		
	private LinkedHashMap<Integer, Integer> map2;
	private final int CAPACITY2;

	public LRUCache(int capacity) {
		CAPACITY2 = capacity;
		map2 = new LinkedHashMap<Integer, Integer>(capacity, 0.75f, true) {
			/**
			 * 
			 */
			private static final long serialVersionUID = 1L;

			protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
				return size() > CAPACITY2;
			}
		};
	}

	public int get2(int key) {
		return map2.getOrDefault(key, -1);
	}

	public void put2(int key, int value) {
		map2.put(key, value);
	}
	
	}
	
	// https://leetcode.com/problems/lru-cache/discuss/46200/Java-solution-with-doubly-linked-list-hash-map
	
	/** The following is using LinkedHashMap */
	
	// https://leetcode.com/problems/lru-cache/discuss/46055/Probably-the-%22best%22-Java-solution-extend-LinkedHashMap

}
