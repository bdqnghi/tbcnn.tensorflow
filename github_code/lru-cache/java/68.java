package design;

import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Map;

/*
 * Apache LRU Map: http://commons.apache.org/proper/commons-collections/javadocs/api-2.1.1/org/apache/commons/collections/LRUMap.html
 * http://docs.oracle.com/javase/6/docs/api/java/util/LinkedHashMap.html
 * http://stackoverflow.com/questions/221525/how-would-you-implement-an-lru-cache-in-java-6
 */
public class LRU {
	

	private LinkedList<String> queue = new LinkedList<String>();
	private HashMap<String, Object> cache = new HashMap<String, Object>();
	private int size;
	private LRU(int size){
		this.size = size;
	}
	
	Object get(String key){
		if(!cache.containsKey(key)){
			return null;
		}
		queue.remove(key);
		queue.add(key);
		return  cache.get(key);
	}
	
	void put(String key, Object val){
		if(cache.containsKey(key)){
			queue.remove(key);
			queue.add(key);
			return;
		}
		
		cache.put(key, val);
		queue.add(key);
		if(queue.size() > size){
			cache.remove(queue.remove());
		}
	}

	public static void main(String[] args) {
		 Map m = Collections.synchronizedMap(new LinkedHashMap());
	}
}
