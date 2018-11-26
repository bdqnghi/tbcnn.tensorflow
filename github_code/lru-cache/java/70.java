public class Solution {
    class Node {
        int key;
        int val;
        Node next;
        Node pre;
        Node(int key, int val) {
            this.key = key;
            this.val = val;
        }
    }
    
    Node head;
    Node tail;
    Map<Integer, Node> map;
    int capacity;
    int size;
    
    // Notes to be taken from this problem:
    // Classic doubly linkedlist data structure, might be used in ohter problems.
    // Find top K words in given article: min-heap solution!!!! 
    // TripAdvisor actual phone interview question.

    // @param capacity, an integer
    public Solution(int capacity) {
        // write your code here
        this.capacity = capacity;
        this.size = 0;
        map = new HashMap<Integer, Node>();
    }

    // @return an integer
    public int get(int key) {
        // write your code here
        if (map.containsKey(key)) {
            // update the node order in the queue
            // then return the value
            Node oldEntry = map.get(key);
            int val = oldEntry.val;
            // update the order of current node in the queue.
            if (oldEntry == tail) {
                // do nothing
            } else if (oldEntry == head) {
                // move head to tail
                // cut the head and assign next as head
                Node next = oldEntry.next;
                oldEntry.next = null;
                next.pre = null;
                head = next;
                // append previous head to tail
                tail.next = oldEntry;
                oldEntry.pre = tail;
                tail = oldEntry;
            } else {
                // current node is in the middle.
                Node next = oldEntry.next;
                Node pre = oldEntry.pre;
                next.pre = pre;
                pre.next = next;
                oldEntry.next = null;
                oldEntry.pre = tail;
                tail.next = oldEntry;
                tail = oldEntry;
            }
            return val;

        } else {
            return -1;
        }
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // write your code here
        // first check if key exist, if so just update
        // the value and order
        // if not, perform insertion here: should check the
        // capacity.
        if (map.containsKey(key)) {
            // update the existing record
            Node oldEntry = map.get(key);
            oldEntry.val = value;
            // update the order in the queue.
            get(key);
        } else {
            Node newEntry = new Node(key, value);
            map.put(key, newEntry);
            // first check the capacity
            if (size >= capacity) {
                // invalidate the LRU
                // which node should be invalidated?
                // both head and tail might work.
                // Here we insert new values to tail,
                // so that head node is the LRU node.
                Node oldEntry = head;
                int oldKey = oldEntry.key;
                map.remove(oldKey);

                if (oldEntry.next == null) {
                    // LRU is of capacity of one
                    head = newEntry;
                    tail = head;
                } else {
                    // append new record in the tail
                    tail.next = newEntry;
                    newEntry.pre = tail;
                    tail = tail.next;
                    // remove head
                    Node newHead = head.next;
                    // is this line necessary?
                    head.next = null;
                    newHead.pre = null;
                    head = newHead;
                }
            } else {
                // perform insertion
                // append new record in the tail
                if (head == null) {
                    head = newEntry;
                    tail = newEntry;
                } else {
                    tail.next = newEntry;
                    newEntry.pre = tail;
                    tail = tail.next;
                }
                size++;
            }
        }
    }
}
