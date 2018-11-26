package leetcode.com.hard.part1;

import java.util.HashMap;

/**
 * Created by jason on 2016/1/14.
 * Location:
 * https://leetcode.com/problems/lru-cache/
 * http://www.jiuzhang.com/solutions/lru-cache/
 * ******************************************************
 * Descriptions:
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and set.
 * <p>
 * get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 * set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity,
 * it should invalidate the least recently used item before inserting a new item.
 * ******************************************************
 * Solutions:
 * 数据结构为双向链表，在Cache中留存头结点（Least used node）和尾结点（newest node），
 * Set操作流程：
 * 1.key存在，则更新value值，return
 * 2.若链表已满，删除head结点的Node，重新设置head结点  -->其实这个的capacity是由于HashMap来控制的
 * 3.将结点插入链表
 * 4.将新结点移到tail结点
 * Get操作：
 * 1.key不存在：返回-1
 * 2.key存在时，提取结点，设置其为尾结点
 * 3.返回结点的value
 * 当链表满员时候，
 * 整体而言采用的是hash来处理key-value的关系，用双向链表来管理增删移动结点，这是一个复合的数据结构处理
 * ******************************************************
 * Bug:
 * 有3个地方出现了错误，原因和异常的现象写在了后面代码中
 */
public class No146_LRU_Cache {

    public static void main(String[] args) {
        No146_LRU_Cache lru = new No146_LRU_Cache(2);
//        lru.get(2);
        lru.set(2, 1);
        lru.set(1, 1);
        lru.set(2, 3);
        lru.set(4, 1);
        lru.get(1);
        lru.get(2);
//        lru.set(1, 5);
//        lru.get(1);
    }

    private class Node {
        public Node prev;
        public Node next;
        private int value;
        private int key;//bug #2  因为这个可以，没有索引的作用，索引直接设个-1即可。

        public Node(int key, int value) {
            this.value = value;
            this.key = key;
        }

        public int getValue() {
            return value;
        }

        public void setValue(int value) {
            this.value = value;
        }
    }

    private Node head;
    private Node tail;
    private int capacity;
    private HashMap<Integer, Node> doublyList;

    public No146_LRU_Cache(int capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head.prev = tail;
        head.next = tail;
        tail.prev = head;
        tail.next = head;
        doublyList = new HashMap<>(capacity);
        this.capacity = capacity;

    }

    public int get(int key) {
        if (!doublyList.containsKey(key)) {
            return -1;
        }
        Node node = isolateNode(doublyList.get(key));
        moveToHead(node);
        return doublyList.get(key).getValue();

    }

    public void set(int key, int value) {

        if (get(key) != -1) {//#bug 3 可以使用刚刚做成的get(key)方法
            doublyList.get(key).setValue(value);
            return;//bug #1 忘记返回的话，就会直接执行后面的代码，导致数据结构中的数据不准确
        }

        if (capacity == doublyList.size()) {
            Node node = isolateNode(tail.prev);
            doublyList.remove(node.key);//?
        }

        Node newNode = new Node(key, value);
        doublyList.put(key, newNode);
        moveToHead(newNode);

    }

    private Node isolateNode(Node node) {

        node.next.prev = node.prev;
        node.prev.next = node.next;

        return node;
    }

    private void moveToHead(Node newNode) {

        head.next.prev = newNode;
        newNode.next = head.next;
        head.next = newNode;
        newNode.prev = head;
    }
}
