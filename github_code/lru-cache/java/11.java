import java.util.LinkedHashMap;
import java.util.Map;

/**
 * hujiawei 15/4/23
 * <p/>
 * 链表 146题，本题特殊原因没加上题目编号
 * <p/>
 * https://leetcode.com/problems/lru-cache/
 */
public class LRUCache_146 extends LinkedHashMap<Integer, Integer> {

    int capacity;

    public LRUCache_146(int capacity) {
        super(capacity, 0.75f, true);
        this.capacity = capacity;
    }

    public int get(int key) {
        Integer v = get((Object) key);
        if (v != null) {
            return v;
        }
        return -1;
    }

    @Override
    protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest) {
        return size() > this.capacity;
    }

    public void set(int key, int value) {
        put(key, value);
    }
}
