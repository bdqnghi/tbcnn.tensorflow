/**
* https://www.interviewbit.com/problems/lru-cache/
*
* Based on Java's LinkedHashMap.
*/
public class LruCacheA {
    private final int capacity;
    private final LinkedHashMap<Integer, Integer> cache;
    
    public Solution(int capacity) {
        this.capacity = capacity;
        
        cache = new LinkedHashMap<Integer, Integer>(16, 0.75f, true) {
            protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
                return size() > capacity;
            }
        };
    }
    
    public int get(int key) {
        return cache.getOrDefault(key, -1);
    }
    
    public void set(int key, int value) {
        cache.put(key, value);
    }
}
