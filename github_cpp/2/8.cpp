













#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

struct CacheNode {
    int key;
    int value;
    CacheNode(int k, int v) : key(k), value(v) {};
};

class LRUCache{
public:
    LRUCache(int capacity) {
        _cap = capacity;
    }

    int get(int key) {
        if (!_map.count(key)) return -1;
        move(key);
        return _map[key]->value;
    }

    void set(int key, int value) {
        if (_map.count(key)) {
            _map[key]->value = value;
            move(key);
        }
        else {
            if (_cap == _map.size()) {
                _map.erase(_list.back().key);
                _list.pop_back();
            }
            _list.push_front(CacheNode(key, value));
            _map[key] = _list.begin();
        }
    }

private:
    void move(int key) {
        auto it = _map[key];
        _list.push_front(*it);
        _list.erase(it);
        _map[key] = _list.begin();
    }

    int _cap;
    list<CacheNode> _list;
    unordered_map<int, list<CacheNode>::iterator> _map;
};

int main() {
    return 0;
}
