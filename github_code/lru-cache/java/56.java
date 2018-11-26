/**
 * 
 */
package com.zeva.utils;
import java.util.*;
/**
 * @author Sapan Bandi
 *
 */
public class LRUCache {

	/**
	 * 
	 */
	public LRUCache() {
		// TODO Auto-generated constructor stub
	}
	
private HashMap<String, DoubleLinkedListNode> map 	= new HashMap<String, DoubleLinkedListNode>();
private DoubleLinkedListNode head;
private DoubleLinkedListNode end;
private int capacity;
private int len;
private static final String s1 = "";

public LRUCache(int capacity) {
	this.capacity = capacity;
	len = 0;
}

public char[] get(String key) {
	
	if (map.containsKey(key)) {
		DoubleLinkedListNode latest = map.get(key);
		removeNode(latest);
		setHead(latest);
		return latest.val;
	} else {
		return s1.toCharArray();
	}
}

public void removeNode(DoubleLinkedListNode node) {
	DoubleLinkedListNode cur = node;
	DoubleLinkedListNode pre = cur.pre;
	DoubleLinkedListNode post = cur.next;

	if (pre != null) {
		pre.next = post;
	} else {
		head = post;
	}

	if (post != null) {
		post.pre = pre;
	} else {
		end = pre;
	}
}

public void setHead(DoubleLinkedListNode node) {
	node.next = head;
	node.pre = null;
	if (head != null) {
		head.pre = node;
	}

	head = node;
	if (end == null) {
		end = node;
	}
}

/**
 * 
 * @param key
 * @param value
 */
public void set(String key, char[] value) {
	if (map.containsKey(key)) {
		DoubleLinkedListNode oldNode = map.get(key);
		oldNode.val = value;
		removeNode(oldNode);
		setHead(oldNode);
	} else {
		DoubleLinkedListNode newNode = 
			new DoubleLinkedListNode(key, value);
		if (len < capacity) {
			setHead(newNode);
			map.put(key, newNode);
			len++;
		} else {
			map.remove(end.key);
			end = end.pre;
			if (end != null) {
				end.next = null;
			}

			setHead(newNode);
			map.put(key, newNode);
		}
	}
}


}
