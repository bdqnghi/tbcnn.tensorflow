







#include <unordered_map>
#include <list>

using namespace std;

class LRUCache{
    
public:
    struct Element {
        int k,v;
        Element() {
            k = v = -1;
        }
    };
    int _capacity;
    list<Element*> _lru;
    unordered_map<int, list<Element*>::iterator> _cache;
    
    LRUCache(int capacity) {
        Element *p = new Element[capacity];
        for (auto i = 0; i < capacity; ++i) {
            _lru.push_back(p);
            p++;
        }
    }
    
    int get(int key) {
        
        auto it = _cache.find(key);
        if (it == _cache.end()) {
            return -1;
        }
        auto lit = it->second;
        auto val = (*lit)->v;
        updateLRU(it);
        return val;
    }
    
    void set(int key, int value) {
        auto it = _cache.find(key);
        if (it != _cache.end()) {
            auto lit = it->second;
            (*lit)->v = value;
            updateLRU(it);
            return;
        }
        
        auto ptr = _lru.front();
        _lru.pop_front();
        if (ptr->k != -1) {
            _cache.erase(ptr->k);
        }
        ptr->k = key; ptr->v = value;
        _lru.push_back(ptr);
        _cache[key] = std::prev(_lru.end());
        
    }
    
    void updateLRU(unordered_map<int, list<Element*>::iterator>::iterator& it) {
        auto k = it->first;
        auto lit = it->second;
        auto ptr = *lit;
        _lru.erase(lit);
        _lru.push_back(ptr);
        _cache[k] = std::prev(_lru.end());
    }
};
