


#include <list>

class LRUCache {
public:
    LRUCache(int capacity) : capa_(capacity) {
    }
    
    int get(int key) {
        if (map_.find(key) != map_.end()) {
            
            const auto value = map_[key]->second;
            update(key, value);
            return value;
        } else {
            return -1;
        }
    }
    
    void set(int key, int value) {
        
        if (map_.find(key) == map_.end() && list_.size() == capa_) {
            auto del = list_.back(); list_.pop_back();
            map_.erase(del.first);
        }
         update(key, value);
    }
    
private:
    list<pair<int, int>> list_; 
    unordered_map<int, list<pair<int, int>>::iterator> map_; 
    int capa_;
    
    
    void update(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            list_.erase(it->second);
        }
        list_.emplace_front(key, value);
        map_[key] = list_.begin();
    }
};
