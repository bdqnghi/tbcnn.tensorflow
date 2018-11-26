// http://stackoverflow.com/questions/2504178/lru-cache-design

#include <list>
#include <unordered_map>
#include <iostream>
using namespace std;

// -----------------------------------------------------------------------------------------
// Class LRUCache
//
// Maintain a list to store the 'key' and 'value' pair
// Maintain a MAP to store the 'key' and the 'iterator' position
// -----------------------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------------------
// Utility function to print the LRU list
// -----------------------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------------------
// Value is always positive. If key is not present return -1
// -----------------------------------------------------------------------------------------
int
LRUCache::get(int key)
{
    auto itr = _lruMap.find(key);
    if (itr == _lruMap.end())
    {
        return -1;
    }

    // Now update the Cache by erasing this entry and reinserting it at the front
    _lruList.erase(itr->second);
    _lruMap.erase(itr);

    _lruList.push_front(make_pair(key, itr->second->second));
    _lruMap[key] = _lruList.begin();

    // Return the Value corresponding to the Key
    // The iterator's second points to the iterator in the list
    // Doing a '*' on it will give the corresponding value
    return itr->second->second;
}

// -----------------------------------------------------------------------------------------
// Set the value corresponding to the key OR
// Insert the value corresponding to the key
// If not space, remove the last used entry from the cache
// -----------------------------------------------------------------------------------------
void
LRUCache::set(int key, int value)
{
    auto itr = _lruMap.find(key);

    // If the entry is present, delete the entry and add it again to the front
    if (itr != _lruMap.end())
    {
        _lruList.erase(itr->second);
        _lruMap.erase(itr);
    }

    // Insert the 'key' and 'value' into the List
    // Insert the 'key' and 'iterator' into the Map
    _lruList.push_front(make_pair(key, value));
    _lruMap[key] = _lruList.begin();
     

    // If we have reached the capacity, delete the last entry
    if (_capacity + 1 == _lruList.size())
    {
        auto itr = _lruList.end();

        // Come to the last element and delete it from the List and the Map
        --itr;
        _lruList.pop_back();
        _lruMap.erase(itr->first);
    }
}

// -----------------------------------------------------------------------------------------
// Main Function
// -----------------------------------------------------------------------------------------
int main()
{
    std::cout << "LRU Cache\n";

    LRUCache lruCache(1);
    lruCache.set(2, 1);
    cout << lruCache.get(2) << endl;

    /*
    LRUCache lruCache(5);
    lruCache.set(1, 100);
    lruCache.set(2, 200);
    lruCache.set(3, 300);
    lruCache.set(4, 400);
    lruCache.set(5, 500);
    lruCache.set(6, 600);
    lruCache.printLRUCacheList();

    cout << lruCache.get(3) << endl;
    lruCache.printLRUCacheList();
    cout << lruCache.get(1) << endl;
    cout << lruCache.get(6) << endl;
    lruCache.printLRUCacheList();
    cout << lruCache.get(2) << endl;
    lruCache.printLRUCacheList();
    cout << lruCache.get(5) << endl;
    lruCache.printLRUCacheList();
    lruCache.set(7, 700);
    lruCache.printLRUCacheList();
    */

    // 3,[set(1,1),set(2,2),set(3,3),set(4,4),get(4),get(3),get(2),get(1),set(5,5),get(1),get(2),get(3),get(4),get(5)]
    cout << endl;
    return 0;
}
