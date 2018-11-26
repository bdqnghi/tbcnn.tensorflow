package com.abin.lee.algorithm.leetcode.lru;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by abin on 2018/8/31.
 * 146. LRU Cache
 * <p>
 * https://leetcode.com/problems/lru-cache/description/
 * https://leetcode.com/problems/lru-cache/discuss/45922/JAVA-Easy-Version-To-Understand!!!!
 */
public class LRUCache {
    private int maxSize;
    private int count;
    private Node head;
    private Node tail;
    private Map<Integer, Node> map;

    public LRUCache(int capacity) {
        map = new HashMap<Integer, Node>();
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head.next = tail;
        tail.pre = head;
        head.pre = null;
        tail.next = null;
        count = 0;
        maxSize = capacity;
    }

    public int get(int key) {
        if (map.get(key) != null) {
            Node node = map.get(key);
            int result = node.value;
            remove(node);
            addHead(node);
            return result;
        }
        return -1;
    }

    public void put(int key, int value) {
        if (map.get(key) != null) {
            Node node = map.get(key);
            node.value = value;
            remove(node);
            addHead(node);
        } else {
            Node node = new Node(key, value);
            map.put(key, node);
            if (count < maxSize) {
                count++;
                addHead(node);
            } else {
                map.remove(tail.pre.key);
                remove(tail.pre);
                addHead(node);
            }
        }
    }

    public void remove(Node node) {
        node.pre.next = node.next;
        node.next.pre = node.pre;
    }

    public void addHead(Node node) {
        node.next = head.next;
        head.next.pre = node;
        head.next = node;
        node.pre = head;


    }

    public static void main(String[] args) {
        LRUCache lru = new LRUCache(3);
        lru.put(1, 11);
        lru.put(2, 22);
        lru.put(3, 33);
        System.out.println("lru.map=" + lru.map);
        lru.get(1);
        lru.get(3);
        lru.get(2);
        System.out.println("lru.map=" + lru.map);
        lru.put(4, 44);
        lru.get(4);
        System.out.println("lru.map=" + lru.map);


    }


    public static class Node {
        int key;
        int value;
        Node pre;
        Node next;

        public Node(int key, int value) {
            this.key = key;
            this.value = value;
        }
    }

}
