/**
 * Author:Jincheng
 * Date:180418
 * Complexity: Time O(1) Space O(N)
 * Description: List + unordered_map
 *              http://www.cnblogs.com/grandyang/p/4587511.html
 *              https://leetcode.com/problems/lru-cache/discuss/46223/O(1)-unordered_map-+-list-+-splice
 *              https://leetcode.com/problems/lru-cache/discuss/45912/Clean-Short-Standard-C++-solution-NOT-writing-C-in-C++-like-all-other-lengthy-ones
 */

class LRUCache {

private:
    
    // capacity of list
    int capacity;
    // List<pair<key,value>>
    list<pair<int,int>> items;
    // map item to it's position in list
    unordered_map<int, list<pair<int,int>>::iterator> cache;
    
public:
    LRUCache(int capacity):capacity(capacity) {
        
    }
    
    int get(int key) {
        
        auto it = cache.find(key);
        
        // the key dont't exit
        if(it == cache.end())
            return -1;
        
        // move the item to the beginning of list
        items.splice(items.begin(),items,it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        
        auto it = cache.find(key);
        
        // if the item exist, erase it firstly
        if(it != cache.end())
        {
            items.erase(it->second);
        }
        // put the item at the beginning of the list
        items.push_front(make_pair(key,value));
        
        // update the cache
        cache[key] = items.begin();
        
        // if beyong the capacity, erase the last item
        if(items.size() > capacity)
        {
            auto key = items.rbegin()->first;
            items.pop_back();
            cache.erase(key);
        }
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

