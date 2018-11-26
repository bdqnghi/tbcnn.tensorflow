/*
    Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.
		get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
		set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, 
		it should invalidate the least recently used item before inserting a new item.

    Link: http://www.lintcode.com/en/problem/lru-cache/

    Example: None

    Solution: Use a list and a map to implement get and set key,value information. 

    Source: https://github.com/kamyu104/LintCode/blob/master/C%2B%2B/lru-cache.cpp
*/

#include <list>

class LRUCache{
public:
    // @param capacity, an integer
    LRUCache(int capacity) : capa_(capacity) {
        // write your code here
    }
    
    // @return an integer
    int get(int key) {
        // write your code here
        auto it = map_.find(key);
        if (it != map_.end()) {
            // It key exists, update it.
            auto l_it = it->second;
            int value = l_it->second;
            update(it, value);
            return value;
        } else {
            return -1;
        }
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    void set(int key, int value) {
        // write your code here
        auto it = map_.find(key);
        // It key exists, update it.
        if (it != map_.end()) {
            update(it, value);
        } else {
            // If cache is full, remove the last one.
            if (list_.size() == capa_) {
                auto del = list_.back(); list_.pop_back();
                map_.erase(del.first);
            }
            list_.emplace_front(key, value);
            map_[key]=list_.begin();
        }
    }
    
private:
    list<pair<int, int>> list_; // key, value
    unordered_map<int, list< pair<int, int>>::iterator> map_; // key, list iterator
    int capa_;

    // Update (key, iterator of (key, value)) pair
    void update(unordered_map<int, list<pair<int, int>>::iterator>::iterator it, int value) {
        auto l_it = it->second;
        int key = l_it->first;
        list_.erase(l_it);
        list_.emplace_front(key, value);
        it->second = list_.begin();
    }
};