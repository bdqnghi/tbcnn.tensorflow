package leetcode.others;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * 
 * @author I319213
 *
 *https://leetcode.com/problems/lru-cache/
 */
public class LRUCache {
    private Map<Integer, Integer> map;
    private int capacity;

    public LRUCache(int capacity) {
	    map=new LinkedHashMap<Integer, Integer>(capacity, 1, true); //set access order to true
	    this.capacity = capacity;
    }

    //beacuse of setting access order, when get you change the order.....?....
    public int get(int key) {
	    if (!map.containsKey(key)) 
	    	return -1;
	    return map.get(key);
    }

    public void set(int key, int value) {
	    if (!map.containsKey(key) && (map.size() == capacity)) {
	        map.remove(map.keySet().iterator().next());
	    }
	    map.put(key, value);
    }

}
