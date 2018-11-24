class LRUCache {
public:
    
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator>hash;
    int capacity;
    LRUCache(int n): capacity(n){}
    
    int get(int key) {
        if(hash.find(key) != hash.end()){
            pair<int, int> kv = *( hash[key] );
            cache.erase(hash[key]);
            cache.push_back(kv);
            hash[key]= --cache.end();
            return kv.second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(hash.size()+1 > capacity || hash.find(key) != hash.end()){
            list<pair<int, int>>::iterator it = (hash.find(key) != hash.end() )?  hash[key] : cache.begin();
            pair<int, int> kv = *it;
            cache.erase(hash[kv.first]);
            hash.erase(kv.first);
        }
        
        cache.push_back({key, value});
        hash[key]= --cache.end();
    }
};
