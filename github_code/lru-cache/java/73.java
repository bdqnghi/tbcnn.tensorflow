/***
Design and implement a data structure for Least Recently Used (LRU) cache. 
It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, 
otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. 
When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
***/

import java.util.LinkedHashMap;
import java.util.Map;

public class LRUCache {
    
    private Map<Integer, Integer> m;
    
    public LRUCache(int capacity) {
        m = new LinkedHashMap<Integer, Integer>(16, 0.75f, true) {
            protected boolean removeEldestEntry(
                    Map.Entry<Integer, Integer> eldest) {
                return size() > capacity;
            }
        };
    }
    
    public int get(int key) {
        Integer v = m.get(key);
        return v == null ? -1 : v;
    }
    
    public void set(int key, int value) {
        m.put(key, value);
    }
}
