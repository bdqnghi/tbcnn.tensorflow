

class LRUCache {

private:
    
    
    int capacity;
    
    list<pair<int,int>> items;
    
    unordered_map<int, list<pair<int,int>>::iterator> cache;
    
public:
    LRUCache(int capacity):capacity(capacity) {
        
    }
    
    int get(int key) {
        
        auto it = cache.find(key);
        
        
        if(it == cache.end())
            return -1;
        
        
        items.splice(items.begin(),items,it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        
        auto it = cache.find(key);
        
        
        if(it != cache.end())
        {
            items.erase(it->second);
        }
        
        items.push_front(make_pair(key,value));
        
        
        cache[key] = items.begin();
        
        
        if(items.size() > capacity)
        {
            auto key = items.rbegin()->first;
            items.pop_back();
            cache.erase(key);
        }
        
    }
};



