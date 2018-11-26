package com.leetcode.oj;

import java.util.HashMap;

public class LRUCache {
	
	int capacity;
	int size = 0;
	HashMap<Integer, Node> map;
	Node head = new Node(Integer.MIN_VALUE, Integer.MIN_VALUE);
	Node tail = new Node(Integer.MAX_VALUE, Integer.MAX_VALUE);;
	
    
    public LRUCache(int capacity) {
        map = new HashMap<Integer, Node> (capacity+1);
        this.capacity = capacity;
        head.next = tail;
        tail.prev = head;
    }
    
    public int get(int key) {
        Node node = map.get((Integer)key);
        if (node == null) {
        	return -1;
        }
        else {
        	move_to_head(node);
        	return node.value;
        }
    }
    
    public void set(int key, int value) {
    	Node node = map.get((Integer)key);
    	if(node == null) {
    		if(size >= capacity)
    			remove_from_tail();
    		Node newNode = new Node(key, value);
    		map.put((Integer)key, newNode);
    		put_to_head(newNode);
    		size ++;
        }
        else {
            node.value = value;
            move_to_head(node);
        }
    }
    
    void remove_from_tail() {
    	Node to_be_removed = tail.prev;
    	int key = to_be_removed.key;
    	tail.prev = to_be_removed.prev;
    	to_be_removed.prev.next = tail;
    	map.remove((Integer) key);
    	size --;
    }
    
    void move_to_head(Node node) {
    	if (node.prev != head) {
    		node.prev.next = node.next;
    		node.next.prev = node.prev;
    		node.next = head.next;
    		node.prev = head;
    		head.next.prev = node;
    		head.next = node;
    	}
    }
    
    void put_to_head(Node node) {
    	node.prev = head;
    	node.next = head.next;
    	head.next.prev = node;
    	head.next = node;
    }

    class Node {
    	public int key;
    	public int value;
    	public Node prev;
    	public Node next;
    	public Node (int k, int v) {
    		key = k;
    		value = v;
    	}
    }
    
    void print_map() {
    	System.out.print("Size:" + size);
    	Node node = head.next;
    	while (node != tail) {
    		System.out.print(" (" + node.key + "," + node.value + ")");
    		node = node.next;
    	}
    	System.out.println();
    }
    
    public static void main(String[] arg) {
    	LRUCache lrc = new LRUCache(3);
    	
    	lrc.set(1,1);
    	lrc.print_map();
    	lrc.set(2,2);
    	lrc.print_map();
    	lrc.set(3,3);
    	lrc.print_map();
    	lrc.set(4,4);
    	lrc.print_map();
    	
    	System.out.println(lrc.get(4));
    	lrc.print_map();
    	System.out.println(lrc.get(3));
    	lrc.print_map();
    	System.out.println(lrc.get(2));
    	lrc.print_map();
    	System.out.println(lrc.get(1));
    	lrc.print_map();
    	
    	lrc.set(5,5);
    	lrc.print_map();
    	
    	System.out.println(lrc.get(1));
    	lrc.print_map();
    	System.out.println(lrc.get(2));
    	lrc.print_map();
    	System.out.println(lrc.get(3));
    	lrc.print_map();
    	System.out.println(lrc.get(4));
    	lrc.print_map();
    	System.out.println(lrc.get(5));
    	lrc.print_map();
    	
    }
}
















