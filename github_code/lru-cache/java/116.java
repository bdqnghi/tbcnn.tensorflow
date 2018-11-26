/*
@Copyright:LintCode
@Author:   zhou21
@Problem:  http://www.lintcode.com/problem/lru-cache
@Language: Java
@Datetime: 17-04-15 14:23
*/

public class Solution {
    private class Node {
        private int key, val;
        private Node prev, next;
        public Node(int key, int value) {
            this.key= key;
            this.val= value;
            
        }
    }
    private Node head = new Node(-1, -1);
    private Node tail = new Node(-1, -1);
    private int size;
    private Map<Integer, Node> map = new HashMap<Integer, Node>();
    
    // @param capacity, an integer
    public Solution(int capacity) {
        // write your code here
        this.size = capacity;
        head.next = tail;
        tail.prev = head;
    }

    // @return an integer
    public int get(int key) {
        // write your code here
        if (!map.containsKey(key)) {
            return -1;
        }
        Node cur = map.get(key);
        cur.prev.next = cur.next;
        cur.next.prev = cur.prev;
        
        move_to_tail(cur);
        
        return cur.val;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // write your code here
        if (get(key)!=-1) {
            map.get(key).val = value;
            return;
        }
        if (this.size == map.size()) {
            map.remove(head.next.key);
            head.next = head.next.next;
            head.next.prev = head;
        }
        
        Node insert = new Node(key, value);
        move_to_tail(insert);
        map.put(key, insert);
    }
    private void move_to_tail(Node cur) {
        tail.prev.next = cur;
        cur.prev = tail.prev;
        
        tail.prev = cur;
        cur.next = tail; 
    }
}