#include <list>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;


struct KeyValue {
    int key;
    int value;
    KeyValue(int k, int v): key(k), value(v) {}
};

class LRUCache{
public:

    typedef list<KeyValue> FreqSet;
    typedef unordered_map<int, FreqSet::iterator > FMap;
    FMap fmap;
    FreqSet fset; // back is new, front is old
    const int   cap;

    LRUCache(int capacity): cap(capacity) {

    }
    int get(int key) {
        FMap::iterator itm = fmap.find(key);
        if( itm == fmap.end() )
            return -1;

        int v = itm->second->value;
        fset.splice(fset.end(), fset, itm->second);

        return v;
    }
    void set(int key, int value) {
        FMap::iterator itm = fmap.find(key);
        FreqSet::iterator it;
        if( itm == fmap.end() ) {
            fmap[key] = fset.emplace(fset.end(), key,value);
            if( fmap.size() > cap ) {
                // remove LRU
                fmap.erase(fset.front().key);
                fset.pop_front();
            }
        }else{
            it = itm->second;
            it->value = value;
            fset.splice(fset.end(), fset, itm->second);
        }
    }
};

int main_LRUCache()
{
    LRUCache lru(2);

//    cout << lru.get(1) << endl;  // -1
    lru.set(2,1);
    lru.set(1,1);
    lru.set(2,3);
    lru.set(4,1);
    cout << lru.get(1) << endl;
    cout << lru.get(2) << endl;

    return 0;
}
