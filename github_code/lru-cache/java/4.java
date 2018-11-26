package _important;

import java.util.HashMap;

/**
 * Design and implement a data structure for Least Recently Used (LRU) cache. It
 * should support the following operations: get and set.
 * 
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1. set(key, value) - Set or insert the
 * value if the key is not already present. When the cache reached its capacity,
 * it should invalidate the least recently used item before inserting a new
 * item.
 * 
 * @author VictorQian
 * 
 */

/**
 * 用一个hash表加上一个双向链表来实现。基本思路是这样的，用一个hash表来维护结点的位置关系，也就是hash表的key就是资源本身的key，
 * value是资源的结点
 * （包含key和value的信息）。然后把结点维护成一个双向链表构成的队列，这样子如果我们要访问某一个结点，那么可以通过hash表和key来找到结点
 * ，从而取到相应的value。而当我们想要删除或者插入结点时，我们还是通过hash表找到结点，然后通过双向链表和队列的尾结点把自己删除同时插入到队尾。
 * 通过hash表访问结点我们可以认为是O
 * (1)的操作（假设hash函数足够好），然后双向链表的插入删除操作也是O(1)的操作。如此我们便实现了用O(1)时间来完成所有LRU
 * cache的操作。空间上就是对于每一个资源有一个hash表的的项以及一个对应的结点（包含前后指针和资源的<key, value>）
 * 
 * @author VictorQian
 * 
 */
public class LRUCache {
	class Node {
		Node pre, next;
		int key;
		int val;

		public Node(int key, int value) {
			this.key = key;
			this.val = value;
		}
	}

	private int capacity;
	private int size;
	private HashMap<Integer, Node> map;
	private Node head, tail;

	public LRUCache(int capacity) {
		this.capacity = capacity;
		size = 0;
		map = new HashMap<Integer, Node>();
		head = null;
		tail = null;
	}

	public int get(int key) {
		Node node = map.get(key);
		if (node == null)  //if cound not find the key, return -1.
			return -1;
		else if (node != tail) { //keep tail as the latest access node.
			moveNodeToTail(node);
		}
		return node.val;
	}
	
	public void set(int key, int value) {
		Node node = map.get(key);
		if (node != null) {
			node.val = value;
			if (node != tail) {
				moveNodeToTail(node);
			}
		} else {
			Node newNode = new Node(key, value);
			if (size >= capacity) { //remove the head node.
				map.remove(head.key);
				head = head.next;
				if (head != null)
					head.pre = null;
				else
					tail = null;
				size--;
			}
			if (head == null || tail == null) {
				head = newNode;
			} else {
				tail.next = newNode;
			}
			newNode.pre = tail;
			tail = newNode;
			map.put(key, newNode);
			size++;
		}
	}
	
	private void moveNodeToTail(Node node){
		if (node == head)    //if node == head,  move the head to its next.
			head = head.next;
		else // 1<->k<->3   ===>  1<->3   skip the node.
			node.pre.next = node.next;
		
		node.next.pre = node.pre;
		//move the node to tail.
		tail.next = node;
		node.pre = tail;
		node.next = null;
		tail = node;
	}
}
