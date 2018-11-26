package wang.c10;

import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;

public class LRU {

    private LinkedHashMap<Integer, Integer> map;

    public LRU(final int capacity){
        map=new LinkedHashMap<Integer, Integer>(16, 0.75f, true){
            @Override
            protected boolean removeEldestEntry(Map.Entry<Integer, Integer> eldest){
                return size()> capacity;
            }
        };
    }

    public int get(int key){
        Integer value=map.get(key);
        if(value==null) {
            return -1;
        }
        return value;
    }

    public void set(int key, int value){
        map.put(key, value);
    }

    public Set<Integer> keySet(){
        return map.keySet();
    }

    public Collection<Integer> values(){
        return map.values();
    }

    public Set<Map.Entry<Integer, Integer>> entrySet(){
        return map.entrySet();
    }

    public static void main(String[] args) {
        // TODO Auto-generated method stub
        LRU cache= new LRU(10);
        for(int i=1; i<=18; i++){
            cache.set(i, i);
        }

        System.out.println(cache.keySet() + " , "+ ( cache.keySet() instanceof Set<?>) ); 
        Iterator<Integer> iterator=cache.keySet().iterator();
        while(iterator.hasNext()){
            Integer e=iterator.next();
            System.out.print( e + " , ");

        }
        System.out.println("\nvalues: "+cache.values());
        System.out.println("\nentry set: "+cache.entrySet());
        for(Map.Entry<Integer, Integer> e: cache.entrySet()){
            System.out.println( e.getKey() + ",  "  + e.getValue() );
        }

    }

}
