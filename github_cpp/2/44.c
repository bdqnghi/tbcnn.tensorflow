

#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;







class LRUCache
{
private:
    int _capacity;
    list<pair<int, int> > _lruList;
    unordered_map<int, list<pair<int,int>>::iterator> _lruMap;

public:
    LRUCache(int capacity);
    int get(int key);
    void set(int key, int value);
    void printLRUCacheList();
};

LRUCache::LRUCache(int capacity) :
          _capacity(capacity)
{ }




void
LRUCache::printLRUCacheList()
{
    cout << endl << "LRU Cache" << endl;
    for (auto itr = _lruList.begin(); itr != _lruList.end(); ++itr)
    {
        cout << (itr->first) << " : " << (itr->second) << endl;
    }
    cout << endl;
}




int
LRUCache::get(int key)
{
    auto itr = _lruMap.find(key);
    if (itr == _lruMap.end())
    {
        return -1;
    }

    
    _lruList.erase(itr->second);
    _lruMap.erase(itr);

    _lruList.push_front(make_pair(key, itr->second->second));
    _lruMap[key] = _lruList.begin();

    
    
    
    return itr->second->second;
}






void
LRUCache::set(int key, int value)
{
    auto itr = _lruMap.find(key);

    
    if (itr != _lruMap.end())
    {
        _lruList.erase(itr->second);
        _lruMap.erase(itr);
    }

    
    
    _lruList.push_front(make_pair(key, value));
    _lruMap[key] = _lruList.begin();
     

    
    if (_capacity + 1 == _lruList.size())
    {
        auto itr = _lruList.end();

        
        --itr;
        _lruList.pop_back();
        _lruMap.erase(itr->first);
    }
}




int main()
{
    std::cout << "LRU Cache\n";

    LRUCache lruCache(1);
    lruCache.set(2, 1);
    cout << lruCache.get(2) << endl;

    

    
    cout << endl;
    return 0;
}
