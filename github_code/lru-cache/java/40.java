/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
*/

// Solution 1.
// Use a LinkedHashMap.

import java.util.LinkedHashMap;
import java.util.Map.Entry;
public class LRUCache extends LinkedHashMap<Integer, Integer> {
   
    private int capacity;
   
    public LRUCache(int capacity) {
        super(capacity, 1.0f, true);  // for access order (if false, then insertion order). 1.0f is the fill ratio
        this.capacity = capacity;
    }
   
    public int get(int key) {
        if(super.get(key) == null)
            return -1;
        else
            return ((int) super.get(key));
    }
   
    public void set(int key, int value) {
        super.put(key, value);
    }
    
    // override. If size is greater than capacity after an add, remove the oldest entry.
    protected boolean removeEldestEntry(Entry entry) {
        return (size() > this.capacity);
    }
}

// Solution 2. 
// Use a Hashmap<Integer,Node> and a doubly linkedList.
// Implement 2 extra method, remove(Node n) and setHead(Node n).

public class LRUCache {
    public class Node{
        int key;
        int value;
        Node last = null;
        Node next = null;
        public Node(int key, int value){
            this.key = key;
            this.value = value;
        }
    }
    
    int capacity;
    Map<Integer,Node> hm;
    Node head = null;
    Node end = null;
    
    public LRUCache(int capacity) {
        this.capacity = capacity;
        hm = new HashMap<Integer,Node>();
    }
    
    public int get(int key) {
        if(hm.containsKey(key)){
            // get the node corresponding to the key
            Node n = hm.get(key);
            // remove the node from the linked list
            remove(n);
            // add the node to the beginning of the list
            setHead(n);
            // return the value of the Node
            return n.value;
        }
        else return -1;
    }
    
    public void remove(Node n){
        if(n.last!=null){
            n.last.next = n.next;
        }
        else{
            head = n.next;
        }
        
        if(n.next!=null){
            n.next.last = n.last;
        }
        else{
            end = n.last;
        }
        
    }
    
    public void setHead(Node n){
        n.next = head;
        n.last = null;
        // check if head is null before assign head.last;
        if(head!=null){
            head.last = n;
        }
        head = n;
        
        if(end == null){
            end = head;
        }
    }
    public void set(int key, int value) {
        if(hm.containsKey(key)){
            Node n = hm.get(key);
            n.value = value;
            remove(n);
            setHead(n);
        }
        else{
            Node n = new Node(key,value);
            if(hm.size() >= capacity){
                // if capacity is already reached, remove the last element
                hm.remove(end.key);
                remove(end);
                setHead(n);
            }
            else{
                setHead(n);
            }
            hm.put(key,n);
        }
    }
}
