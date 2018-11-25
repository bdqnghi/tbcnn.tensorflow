class LRUCache{
private:
    struct CacheNode {
        int key, value;
        CacheNode(int k, int v):key(k), value(v) {}
    };
    
    std::list<CacheNode> cacheList;
    std::unordered_map<int, std::list<CacheNode>::iterator> cacheMap;
    int capacity;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (cacheMap.find(key) == cacheMap.end()) 
            return -1;
        
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->value;
    }
    
    void set(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            if (capacity == cacheList.size()) { 
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            
            
            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
        else {
            
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
            cacheMap[key]->value = value;
        }
    }
};
