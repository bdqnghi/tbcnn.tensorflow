#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

// ------------------------------------------------------------------------------------------------
// Class LRUCache
//      New elements gets inserted to the Last. 
// ------------------------------------------------------------------------------------------------
class LRUCache
{
private:
    int _capacity;
    vector<int> _lruVector;
    // Key will the data
    // Value will be the position where it is stored in the vector
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
//          _lruVector(capacity, 0)
{ }

// Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1
int
LRUCache::get(int key)
{
    auto itr = _lruMap.find(key);
    if (itr != _lruMap.end())
    {
        // If the element is present, remove it from the vector
        cout << "Itr: " << itr->second << endl;
        _lruVector.erase(_lruVector.begin() + itr->second);

        // Now push the element to the end of the list
        _lruVector.push_back(key);
        _lruMap[key] = _lruVector.size() - 1;

        // Value in Map will be the position in the Vector that has the Value for the Key
        return _lruVector[_lruVector.size() - 1];
    }

    return -1;
}

// Set or insert the value if the key is not already present
// When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
void
LRUCache::set(int key, int value)
{
    // Update the Value first by finding the element in the Map
    auto itr = _lruMap.find(key);
    if (itr != _lruMap.end())
    {
        // If the element is present, remove it from the vector
        _lruVector.erase(_lruVector.begin() + itr->second);
    }
    else
    {
        // Element is not present
        if (_lruVector.size() == _capacity)
        {
            // Remove the first element
            _lruVector.erase(_lruVector.begin());
        }
    }

    // Now push the element to the end of the list
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

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
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
