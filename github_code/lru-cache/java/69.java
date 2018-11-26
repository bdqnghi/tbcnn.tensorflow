/*
 * Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, 
it should invalidate the least recently used item before inserting a new item.
 */
import java.util.*;
public class LRUCache {
    public class LRUNode{
        int key;
        int val;
        LRUNode prev;
        LRUNode next;
        
        public LRUNode(int k, int value)  {
            key = k;
            val = value;
        }      
    }
    
    private HashMap<Integer,LRUNode> map;
    private int size;
    private LRUNode head;
    private LRUNode tail;

    public LRUCache(int capacity) {
        size = capacity;
        map = new HashMap<Integer,LRUNode>();
        head = null;
        tail = null;
                
    }
    
    // insert the node to the head of list
    private void insertHead(LRUNode node) {
        node.prev = null;
        node.next = head;
        if (head != null)
            head.prev = node;
        head = node;
        if (tail == null)
            tail = head;
    }
    // remove the tail node
    private void remove(LRUNode node) {

        if (node.prev != null)
            node.prev.next = node.next;
        else 
            head = node.next;
        
        if (node.next != null)
            node.next.prev = node.prev;
        else
            tail = node.prev;
    }
    
    public int get(int key) {
        // search in the Hash Map
        LRUNode result = map.get(key);
        // return -1 if didn't find the key
        if (result == null)
            return -1;
        remove(result);
        insertHead(result);
        
        return result.val;
    }
    
    public void set(int key, int value) {
        // search in the Hash Map
        LRUNode node = map.get(key);
        // if the key is already in the LRU cache
        if (node != null) {
            // set the new value
            node.val = value;
            // move the node to the head
            remove(node);
            insertHead(node);
            return;
        }
        // if it is full
        if (size == map.size()) {
            //remove the last node
            int k = tail.key;
            remove(tail);
            map.remove(k);
        }
        node = new LRUNode(key, value);
        map.put(key, node);
        insertHead(node);
    }
    
    public static void main(String args[]) {
        
        LRUCache c = new LRUCache(1);
        /*
        c.set(2, 1);
        System.out.println(c.get(2));
        c.set(3, 2);
        System.out.println(c.get(2));
        System.out.println(c.get(3));
        */
        c = new LRUCache(2);
        
        c.set(2, 1);
        c.set(1, 1);
        System.out.println(c.get(2));
        c.set(4, 1);
        System.out.println(c.get(1));
        System.out.println(c.get(2));
    }
}
