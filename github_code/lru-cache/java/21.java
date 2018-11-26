class LRUCache {
    
    HashMap<Integer, Integer> lru;
    LinkedList<Integer> queue;
    int capacity;
    
    public LRUCache(int capacity) {
        this.capacity = capacity;
        lru = new HashMap<>();
        queue = new LinkedList<>();
    }
    
    public int get(int key) {
        if (!lru.containsKey(key)) {
            return -1;
        }
        int index = queue.indexOf(key);
        queue.remove(index);
        queue.add(key);
        return lru.get(key);        
    }
    
    public void put(int key, int value) {
        if (lru.containsKey(key)) {
            lru.replace(key, value);
            int index = queue.indexOf(key);
            queue.remove(index);
            queue.add(key);
        }
        else {
            if (lru.size() < capacity) {
                lru.put(key, value);
                queue.add(key);
            }
            else {
                int index = queue.poll();
                lru.remove(index);
                lru.put(key, value);
                queue.add(key);
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
