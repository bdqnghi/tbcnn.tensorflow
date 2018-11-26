package leetcode;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * Created by Aleksandr on 05/07/2017.
 * Project Solutions
 * <p>
 * https://leetcode.com/problems/lru-cache
 */
public class LruCache {
    private int capacity = 0;
    private LinkedHashMap<Integer, Integer> map;

    public LruCache(int capacity) {
        this.capacity = capacity;
        map = new LinkedHashMap<Integer, Integer>(capacity, 0.75f, true) {
            @Override
            protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
                return size() > LruCache.this.capacity;
            }
        };
    }

    public int get(int key) {
        return map.getOrDefault(key, -1);
    }

    public void put(int key, int value) {
        map.put(key, value);
    }
}
