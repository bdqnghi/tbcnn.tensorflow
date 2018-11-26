// Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
//
//
//
// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.


public class LRUCache {
    private class Node{
        Node prev;
        Node next;
        int key;
        int value;

        public Node(int key, int value){
            this.key = key;
            this.value = value;
            this.prev = null;
            this.next = null;
        }
    }

    private int capacity;
    private HashMap<Integer, Node> hash = new HashMap<Integer, Node>();
    private Node head = new Node(-1, -1);
    private Node tail = new Node(-1, -1);
    
    public LRUCache(int capacity) {
        this.capacity = capacity;
        tail.prev = head;
        head.next = tail;
    }
    
    public int get(int key) {
        if (!hash.containsKey(key)){
            return -1;
        }
        // remove current node
        Node current = hash.get(key);
        current.prev.next = current.next;
        current.next.prev = current.prev;
        // move current node to tail
        movetotail(current);

        return hash.get(key).value;
    }
    
    public void set(int key, int value) {
        if (get(key) != -1) {
            hash.get(key).value = value;
            return;
        }

        if (hash.size() == capacity) {
            hash.remove(head.next.key);
            head.next = head.next.next;
            head.next.prev = head;
        }

        Node insert = new Node(key, value);
        hash.put(key, insert);
        movetotail(insert);
    }
    private void movetotail(Node current) {
        current.prev = tail.prev;
        tail.prev = current;
        current.prev.next = current;
        current.next = tail;
    }
}


