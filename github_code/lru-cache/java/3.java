package zhy2002.leetcode.solutions.lrucache;

/**
 * https://leetcode.com/problems/lru-cache/
 */
public class LRUCache {

    private java.util.LinkedHashMap<Integer, Integer> storage = new java.util.LinkedHashMap<>();
    private int capacity;

    public LRUCache(int capacity) {
        this.capacity = capacity;
    }

    public int get(int key) {
        Integer value = storage.get(key);
        if(value == null){
            return -1;
        }
        storage.remove(key);
        storage.put(key, value);
        return value;
    }

    public void set(int key, int value) {
        Integer val = storage.get(key);
        if (val == null && storage.size() == capacity) {
            storage.remove(storage.keySet().iterator().next());
        } else if (val != null) {
            storage.remove(key);
        }
        storage.put(key, value);
    }
}
