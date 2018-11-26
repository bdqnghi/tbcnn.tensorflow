/*
@Copyright:LintCode
@Author:   vadxin
@Problem:  http://www.lintcode.com/problem/lru-cache
@Language: Java
@Datetime: 16-08-30 07:24
*/

class Node {
    public Node pre;
    public Node next;
    public int key;
    public int val;
    public Node(int key, int value) {
        this.key = key;
        this.val = value;
        this.pre = null;
        this.next = null;
    }    
}
public class Solution {
    public Node head;
    public Node tail;
    public int capacity;
    public Map<Integer, Node> nodes;
    // @param capacity, an integer
    public Solution(int capacity) {
        // write your code here
        this.head = new Node(Integer.MAX_VALUE, Integer.MAX_VALUE);
        this.tail = new Node(Integer.MIN_VALUE, Integer.MIN_VALUE);
        head.next = tail;
        tail.pre = head;
        this.capacity = capacity;
        nodes = new HashMap<Integer, Node>();
    }

    // @return an integer
    public int get(int key) {
        // write your code here
        if (!nodes.containsKey(key)) {
            return -1;
        }
        Node cur = nodes.get(key);
        cur.pre.next = cur.next;
        cur.next.pre = cur.pre;
        move_to_tail(cur);
        return cur.val;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // write your code here
        if (get(key) == -1) {
            Node newNode = new Node(key, value);
            if (nodes.size() >= capacity) {
                nodes.remove(head.next.key);
                head.next = head.next.next;
                head.next.pre = head;
            }
            nodes.put(key, newNode);
            move_to_tail(newNode);
        } else {
            Node cur = nodes.get(key);
            cur.val = value;
            cur.pre.next = cur.next;
            cur.next.pre = cur.pre;
            move_to_tail(cur);
        }
        return;
    }
    
    public void move_to_tail(Node cur) {
        tail.pre.next = cur;
        cur.pre = tail.pre;
        cur.next = tail;
        tail.pre = cur;
    }
}