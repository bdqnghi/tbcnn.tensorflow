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
        // 把当前访问的结点移到链表头部，并更新map中该结点的地址
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->value;
    }
    
    void set(int key, int value) {
        if (cacheMap.find(key) == cacheMap.end()) {
            if (capacity == cacheList.size()) { // 删除链表尾部结点（最少访问结点）
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            
            //插入新结点到链表头部，并在map中记录结点
            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
        else {
            // 把当前访问的结点移动到链表头部，更新map中该结点的位置，并更新结点的值。
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
            cacheMap[key]->value = value;
        }
    }
};
