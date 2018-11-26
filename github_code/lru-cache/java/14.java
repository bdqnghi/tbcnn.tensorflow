// https://leetcode.com/problems/lru-cache/description/

// https://leetcode.com/problems/lru-cache/description/

class LRUCache {

    private HashMap<Integer, Node> map;
    private int maxCapacity;
    private Node head, tail;
    
    public LRUCache(int capacity) {
        this.map = new HashMap<Integer, Node>(capacity, 1.0f);
        this.maxCapacity = capacity;
        this.head = this.tail = null;
    }
    
    public int get(int key) {
        if (this.map.containsKey(key)) {
            Node n = this.map.get(key);
            this.deleteNode(n); // remove
            this.addNode(n);    // add at head
            return n.value;
        }
        return -1;
    }
    
    public void put(int key, int value) {
        
        // remove duplicate entry
        if (this.map.containsKey(key)) {
            Node x = this.map.get(key); // get old value
            this.deleteNode(x);         // remove node from linked list
        }
        
        Node n = new Node(key, value);
        this.addNode(n);
        this.map.put(key, n);
        
        // if above capacity then reduce size
        if (this.map.size() > this.maxCapacity) {
            this.map.remove(this.tail.key);
            this.deleteNode(this.tail);
        }
    }
    
    // add node at head of linked list
    private void addNode(Node n) {
        n.next = this.head;
        if (this.head != null)
            this.head.prev = n;
        else
            this.tail = n;  // head == null implies empty linked list
        this.head = n;
    }
    
    // delete node from middle of linked list
    private void deleteNode(Node n) {
        if (n.next != null)
            n.next.prev = n.prev;
        if (n.prev != null)
            n.prev.next = n.next;
        if (this.tail == n)
            this.tail = n.prev;
        if (this.head == n)
            this.head = n.next;
        n.prev = null;
        n.next = null;
    }
}

class Node {
    Node prev, next;
    int value, key;
    
    Node (int key, int value) {
        this.next = this.prev = null;
        this.value = value;
        this.key = key;
    }
}

// class LRUCache {

//     private LinkedHashMap<Integer, Integer> map;
//     private int maxCapacity;
    
//     public LRUCache(int capacity) {
//         this.maxCapacity = capacity;
//         this.map = new LinkedHashMap<Integer, Integer>(capacity, 1.0f, true) {
//             protected boolean removeEldestEntry(Map.Entry eldest) {
//                 return size() > maxCapacity;
//             }
//         };
//     }
    
//     public int get(int key) {
//         if (this.map.containsKey(key))
//             return this.map.get(key);
//         return -1;
//     }
    
//     public void put(int key, int value) {
//         this.map.put(key, value);
//     }
// }

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */