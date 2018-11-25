#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;





class LRUCache
{
private:
    int _capacity;
    vector<int> _lruVector;
    
    
    unordered_map<int, int> _lruMap;

    void pushToFront(int);
    void deleteElement(int);

public:
    LRUCache(int capacity);
    int get(int key);
    void set(int key, int value);
    void printLRUCache();
};

LRUCache::LRUCache(int capacity) :
          _capacity(capacity)

{ }


int
LRUCache::get(int key)
{
    auto itr = _lruMap.find(key);
    if (itr != _lruMap.end())
    {
        
        cout << "Itr: " << itr->second << endl;
        _lruVector.erase(_lruVector.begin() + itr->second);

        
        _lruVector.push_back(key);
        _lruMap[key] = _lruVector.size() - 1;

        
        return _lruVector[_lruVector.size() - 1];
    }

    return -1;
}



void
LRUCache::set(int key, int value)
{
    
    auto itr = _lruMap.find(key);
    if (itr != _lruMap.end())
    {
        
        _lruVector.erase(_lruVector.begin() + itr->second);
    }
    else
    {
        
        if (_lruVector.size() == _capacity)
        {
            
            _lruVector.erase(_lruVector.begin());
        }
    }

    
    _lruVector.push_back(value);
    _lruMap[value] = _lruVector.size() - 1;
}

void
LRUCache::printLRUCache()
{
    if (!_lruVector.empty())
    {
        cout << _lruVector[0];
        for (uint32_t i = 1; i < _lruVector.size(); i++)
        {
            cout << ", " << _lruVector[i];
        }

        cout << endl;
    }
}




int main()
{
    LRUCache lruCache(5);

    lruCache.set(1, 1);
    lruCache.set(2, 2);
    lruCache.set(3, 3);
    lruCache.set(4, 4);
    lruCache.set(5, 5);
    lruCache.set(6, 6);
    lruCache.printLRUCache();
    lruCache.set(7, 7);
    lruCache.printLRUCache();
    lruCache.set(8, 8);
    lruCache.printLRUCache();
    lruCache.set(9, 9);
    lruCache.printLRUCache();
    lruCache.set(10, 10);
    lruCache.printLRUCache();
    cout << endl;

    lruCache.get(6);
    lruCache.printLRUCache();
    lruCache.get(7);
    lruCache.printLRUCache();
    lruCache.get(8);
    lruCache.printLRUCache();
    lruCache.get(9);
    lruCache.printLRUCache();
    lruCache.get(10);
    lruCache.printLRUCache();

    std::cout << "\n";
    return 0;
}
