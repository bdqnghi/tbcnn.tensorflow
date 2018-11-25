







#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;
template <typename KeyType, typename ValueType>
class LRUCache {
    int capacity;
    typedef typename std::pair<KeyType, ValueType> CachePair;
    std::list<CachePair> Cache;
    typedef typename std::list<CachePair>::iterator list_iterator_t;
    unordered_map<KeyType, list_iterator_t> LRUMap;

public:
    void set(KeyType k,ValueType v) {
        auto it = LRUMap.find(k);
        Cache.push_front(make_pair(k,v)); 
        if(it!=LRUMap.end()) { 
            auto cache_it = it->second; 
            Cache.erase(cache_it); 
        }
        LRUMap[k] = Cache.begin(); 
        
        
        if(LRUMap.size() > capacity) {
            auto cache_it = Cache.end(); 
            cache_it--;
            Cache.pop_back();
            LRUMap.erase(cache_it->first);
        }
        
    }
    ValueType get(KeyType k,ValueType r) {
        auto f_it = LRUMap.find(k); 
        if(f_it == LRUMap.end()) { 
            return r;
        } else {
            ValueType v = f_it->second->second; 
            Cache.splice(Cache.begin(), Cache, f_it->second); 
            LRUMap[k] = Cache.begin();
            return v;
        }
    }
    bool exists(KeyType &k) {
        return (LRUMap.find(k)!=LRUMap.end())?true:false;
    }
    LRUCache(int val) : capacity(val) {}
};

int main() {
    LRUCache<string, int> LRU_int(2);
    LRU_int.set("A", 10);
    LRU_int.set("B", 20);
    cout << "get(A) " << LRU_int.get("A",-1) << endl;
    LRU_int.set("C", 20);
    cout << "get(B) " << LRU_int.get("B",-1) << endl;
    LRU_int.set("B", 20);
    cout << "get(B) " << LRU_int.get("B",-1) << endl;
    cout << "get(A) " << LRU_int.get("A",-1) << endl;
    cout << "get(C) " << LRU_int.get("C",-1) << endl;

    return 0;
}

