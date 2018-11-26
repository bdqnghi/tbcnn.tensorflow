package com.github.spbennett;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;

/**
 * Created by sbennett on 7/9/15.
 *
 * LRU Cache implementation in Java
 * Cache maps IDs to Strings.
 */
public class LRU {
    final int CAPACITY = 5;
    ConcurrentHashMap<Integer, String> cache = new ConcurrentHashMap<>(CAPACITY);
    Queue<Integer> lru = new PriorityQueue<>(CAPACITY);

    /**
     * Looks up an item in the cache
     * @param id Integer ID of the item to find in cache.
     * @return Object from cache or null if
     * not in cache.
     */
    String retrieve(Integer id){
        if (!cache.containsKey(id)){
            // Item not in cache.
            return null;
        } else {
            // Item found in cache.
            // Update the LRU and return the item.
            lru.remove(id);
            lru.add(id);
            return cache.get(id);
        }
    }

    void insert(Integer id, String value){
        if (cache.size() == CAPACITY){
            // Lookup LRU and remove it from cache to make
            // room.
            Integer markedForDelete = lru.remove();
            cache.remove(markedForDelete);
        }

        // Add item to cache and update LRU
        cache.put(id, value);
        lru.add(id);
    }

    public static void main (String args[]){
        LRU lru = new LRU();

        for (int i = 0; i < lru.CAPACITY; i++){
            // populate cache
            lru.insert(i, Integer.toString(i));
        }
        //lru.insert(new Integer(1), "ONE");

        System.out.println(lru.retrieve(1));

    }
}
