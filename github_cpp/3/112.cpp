#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <memory>
#include <utility>

using namespace std;

class LRUCache
{
    private:

        //order in this list represents the usage order. head is the most recently used, head - 1 is the 2nd
        //last used ... tail is the least recently used.
        list<int> _lru_list; //list contains the keys
        map<int, pair<list<int>::iterator, int>> _cache; //contains the key mapping to the list iterator and it's value
        unsigned _capacity;

    public:
        LRUCache(unsigned capacity) : _capacity(capacity)
        {

        }

        int get(int key)
        {
            auto it_key_val = _cache.find(key);
            if (it_key_val == _cache.end())
            {
                //can't find the key so return -1
                return -1;
            }
            return it_key_val->second.second;
        }

        void put(int key, int val)
        {
            auto it_key_val = _cache.find(key);
            if (it_key_val != _cache.end())
            {
                //key already exists so move it to the front
                _lru_list.erase(it_key_val->second.first);
                _lru_list.emplace_front(key);
                _cache[key].second = val;
                it_key_val->second.first = _lru_list.begin();
            }
            else
            {
                while (_capacity <= _lru_list.size())
                {
                    //evict least recently used.
                    _cache.erase(_lru_list.back());
                    _lru_list.pop_back();
                }
                //place the key at front
                _lru_list.push_front(key);
                //key not in map so insert it with the new value
                _cache[key] = {_lru_list.begin(), val};
            }
        }

        void print_cache()
        {
            for (auto item : _cache)
            {
                //cout << "(key = " << item.first << " val = " << item.second << ") ";
                cout << "key = " << item.first << " val = " << item.second.second << endl;
            }
            cout << endl;
        }
};

int main(int argc, char** argv)
{
    LRUCache lru(2);

    cout << lru.get(2) << endl;
    lru.put(2,6);
    lru.print_cache();
    cout << lru.get(1) << endl;
    lru.put(1,5);
    lru.print_cache();
    lru.put(1,2);
    lru.print_cache();
    cout << lru.get(1) << endl;
    cout << lru.get(2) << endl;


    return 0;
}
