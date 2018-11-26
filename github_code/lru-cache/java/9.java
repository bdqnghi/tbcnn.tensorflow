/*
Source : https://leetcode.com/problems/lru-cache/
Author : Jiayi Lei
Date   : Jul 23, 2015

Description:
    Design and implement a data structure for Least Recently Used (LRU) cache. 
    It should support the following operations: get and set.

    get(key) - Get the value (will always be positive) of the key if the key 
    exists in the cache, otherwise return -1.
    set(key, value) - Set or insert the value if the key is not already 
    present. When the cache reached its capacity, it should invalidate the 
    least recently used item before inserting a new item.
    
Tags: Data Structure
*/


import java.util.LinkedHashMap;
public class LRUCache {
    Map<Integer, Integer> map;
    public LRUCache(int capacity) {
        map = new LinkedHashMap<Integer, Integer>(16, 0.75f, true){
            protected boolean removeEldestEntry(Map.Entry eldest){
                return map.size() > capacity;
            }
        };
    }
    
    public int get(int key) {
        return map.getOrDefault(key, -1);
    }
    
    public void set(int key, int value) {
        map.put(key, value);
    }
}
