public class LRUCache {
    private class DLNode { // doubly linked node
        int key, value;
        DLNode pre, next;
    }
    
    private void add(DLNode n) {
        n.pre = head;
        n.next = head.next;
        head.next.pre = n;
        head.next = n;
    }
    
    private void remove(DLNode n) {
        DLNode pre = n.pre;
        DLNode next = n.next;
        pre.next = next;
        next.pre = pre;
    }
    
    private void moveToHead(DLNode n) {
        remove(n);
        add(n);
    }
    
    private DLNode popTail() {
        DLNode last = tail.pre;
        remove(last);
        return last;
    } 
    
    private int count, capacity;
    private DLNode head, tail;
    private HashMap<Integer, DLNode> cache;// key -> DLNode

    public LRUCache(int capacity) {
        this.cache = new HashMap<>();
        this.count = 0;
        this.capacity = capacity;
        head = new DLNode();
        head.pre = null;
        tail = new DLNode();
        tail.next = null;
        head.next = tail;
        tail.pre = head;
    }
    
    public int get(int key) {
        DLNode n = cache.get(key); 
        if (n == null) {
            return -1;
        }
        moveToHead(n);
        return n.value;
    }
    
    public void put(int key, int value) {
        DLNode n = cache.get(key);
        if (n != null) {
            n.value = value;
            moveToHead(n);
        } else {
            n = new DLNode();
            n.key = key;
            n.value = value;
            add(n);
            cache.put(key, n);
            if (++count > capacity) {
                DLNode last = popTail();
                cache.remove(last.key);
                count--;
            }
        }
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
