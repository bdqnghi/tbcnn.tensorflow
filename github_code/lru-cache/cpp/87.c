// http://www.lintcode.com/zh-cn/problem/lru-cache/
// https://leetcode.com/problems/lru-cache/
// a. list+unordered_map

#include "lc.h"

class LRUCache{
public:
    // @param capacity, an integer
    LRUCache(int capacity) {
        cap = capacity;
    }

    // @return an integer
    int get(int key) {
        if (hash.find(key) == hash.end()) {
            cout << "-1" << endl;
            return -1;
        }
        auto iter = hash[key];
        cache.splice(cache.begin(), cache, iter);
        hash[key] = cache.begin();
        cout << cache.front().second << endl;
        return cache.front().second;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    void set(int key, int value) {
        if (hash.find(key) == hash.end()) {
            if (cache.size() == cap) {
                auto iter = cache.rbegin();
                hash.erase(iter->first);
                cache.pop_back();
            }
            cache.push_front(make_pair(key, value));
            hash[key] = cache.begin();
        } else {
            auto iter = hash[key];
            cache.splice(cache.begin(), cache, iter);
            hash[key] = cache.begin();
            cache.front().second = value;
        }
    }
    void run() {
        set(2,1),set(1,1),get(2),set(4,1),get(1),get(2);
    }
    int cap;
    list<pair<int, int> > cache;
    unordered_map<int, list<pair<int, int> >::iterator > hash;
};


int main(int argc, char const *argv[]) {
    LRUCache lru(2);
    lru.run();
	return 0;
}
