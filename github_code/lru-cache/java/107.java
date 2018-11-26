/**
 * Refer to
 * http://www.lintcode.com/en/problem/lru-cache/#
 * Design and implement a data structure for Least Recently Used (LRU) cache. 
   It should support the following operations: get and set.
   get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
   set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, 
                     it should invalidate the least recently used item before inserting a new item.
 *
 * Solution
 * http://www.jiuzhang.com/solutions/lru-cache/
*/
// Solution 1: HashMap + DoublyLinkedList
public class LRUCache {
    private class Node {
        int key;
        int val;
        Node prev;
        Node next;
        public Node(int key, int val) {
            this.key = key;
            this.val = val;
            this.prev = null;
            this.next = null;
        }
    }    

    int capacity;
    // Two major structure to build LRU Cache
    // 1. HashMap
    // 2. DoublyLinkedList (head, tail)
    Map<Integer, Node> map = new HashMap<Integer, Node>();
    // Initial dummy nodes as head and tail
    Node head = new Node(-1, -1);
    Node tail = new Node(-1, -1);

    // @param capacity, an integer
    public LRUCache(int capacity) {
        this.capacity = capacity;
        head.next = tail;
        tail.prev = head;
    }

    // @return an integer
    public int get(int key) {
        if(!map.containsKey(key)) {
            return -1;
        }
        // If contains key's mapping Node, remove it
        // from current position and add to tail
        Node current = map.get(key);
        current.prev.next = current.next;
        current.next.prev = current.prev;
        move_to_tail(current);
        return current.val;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // This internal 'get' method will update the key's position in the linked list.
        if(get(key) != -1) {
            map.get(key).val = value;
            return;
        }
        // If already reach capacity, need remove least used node
        // which stores at the start(head.next) of DoublyLinkedList
        if(map.size() == capacity) {
            // Remove from HashMap
            map.remove(head.next.key);
            // Remove from DoublyLinkedList
            head.next = head.next.next;
            head.next.prev = head;
        }
        Node insert = new Node(key, value);
        map.put(key, insert);
        move_to_tail(insert);
    }
    
    private void move_to_tail(Node current) {
        // The order should not change
        current.prev = tail.prev;
        tail.prev = current;
        current.prev.next = current;
        current.next = tail;
    }
}


// Solution 2: HashMap + SingleLinkedList


