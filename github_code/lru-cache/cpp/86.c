// https://leetcode.com/problems/lru-cache/

class LRUCache{
public:
    LRUCache(int capacity) {
        c = capacity;
    }
    
    int get(int key) {
        auto it = h.find(key);
        if (it == h.end()) return -1;
        else {
            touch(it);
            return it->second.first;
        }
    }
    
    void set(int key, int value) {
        auto it = h.find(key);
        if (it!=h.end()) {
            touch(it);
        } 
        else {
            if (h.size()==c) {
                h.erase(q.back());
                q.pop_back();
                
            }
            q.push_front(key);
        }
        h[key] = {value, q.begin()};
    }

private:
    list<int> q;  //better to use double linked list
    unordered_map<int, pair<int, list<int>::iterator>> h;
    int c;
    
private:
   void touch(unordered_map<int, pair<int, list<int>::iterator>>::iterator it) {
       auto key = it->first;
       q.erase(it->second.second);
       q.push_front(key);
       it->second.second = q.begin();
   }
};