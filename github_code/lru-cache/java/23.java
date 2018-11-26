package com.tenniscradle.concepts;

import java.util.LinkedHashMap;
import java.util.Map;

public class LRU {

    // private Map<String,Integer> m = new HashMap<String,Integer>();
    // private SortedMap<String,Integer> lru_cache = Collections.synchronizedSortedMap(new TreeMap<String, Integer>());
   
    private static final int MAX_SIZE = 3;
    
    private LinkedHashMap<String,Integer> lru_cache = new LinkedHashMap<String,Integer>(MAX_SIZE, 0.1F, true){
        @Override
        protected boolean removeEldestEntry(Map.Entry eldest) {
            return(lru_cache.size() > MAX_SIZE);
         }
    };    
    
    public Integer get1(String s){
        return lru_cache.get(s);        
    }
    
    public void displayMap(){
        /**
         * Exception in thread "main" java.util.ConcurrentModificationException
            at java.util.LinkedHashMap$LinkedHashIterator.nextEntry(LinkedHashMap.java:373)
            at java.util.LinkedHashMap$KeyIterator.next(LinkedHashMap.java:384)
            at LRU.displayMap(LRU.java:23)
            at LRU.main(LRU.java:47)
         */
        for(String key : lru_cache.keySet()){
            System.out.println(lru_cache.get(key));
        }
        
//        for(Map.Entry<String, Integer> kv : lru_cache.entrySet()){
//            System.out.println(kv.getKey() + ":" + kv.getValue());
//        }
    }
    
    public void set(String s, Integer val){
        if(lru_cache.containsKey(s)){            
            lru_cache.put(s, get1(s) + val);
        }
        else{
            lru_cache.put(s, val);
        }
    }
    
    public static void main(String[] args) {
        
        LRU lru = new LRU();
        lru.set("Di", 1);
        lru.set("Da", 1);
        lru.set("Daa", 1);
        lru.set("Di", 1);        
        lru.set("Di", 1);
        lru.set("Daa", 2);
        lru.set("Doo", 2);
        lru.set("Doo", 1);        
        lru.set("Sa", 2);
        lru.set("Na", 1);
        lru.set("Di", 1);
        lru.set("Daa", 1);
        
        lru.displayMap();
    
    }
    
}

