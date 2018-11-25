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

        
        
        list<int> _lru_list; 
        map<int, pair<list<int>::iterator, int>> _cache; 
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
                
                return -1;
            }
            return it_key_val->second.second;
        }

        void put(int key, int val)
        {
            auto it_key_val = _cache.find(key);
            if (it_key_val != _cache.end())
            {
                
                _lru_list.erase(it_key_val->second.first);
                _lru_list.emplace_front(key);
                _cache[key].second = val;
                it_key_val->second.first = _lru_list.begin();
            }
            else
            {
                while (_capacity <= _lru_list.size())
                {
                    
                    _cache.erase(_lru_list.back());
                    _lru_list.pop_back();
                }
                
                _lru_list.push_front(key);
                
                _cache[key] = {_lru_list.begin(), val};
            }
        }

        void print_cache()
        {
            for (auto item : _cache)
            {
                
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
