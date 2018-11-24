#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

/* NOTE TO SELF: There seem to be some errors retrieving data. 
    >>> Poor rehashing + no collision handling is the main cause of your woes right now, Self. <<<
    
    TODO:
    > Need some form of collision detection--either separate chaining or open addressing
    > Check out different hash functions (what else could one use outside of the basic hf?)
*/


/* Begin HashTable.h */
template<class K, class V>
struct dataItem {
    K key;
    V data;
    bool hasData;

    dataItem(K _key, V value, bool containsData) : key(_key), data(value), hasData(containsData) {}
};

template<class K, class V>
class HashTable {
private:
    int htSize = 3; //Keep to prime numbers if using mod with hash_func
    dataItem<K, V> *emptyItem = new dataItem<K, V>(K(), V(), false);
    std::vector<dataItem<K, V>*> testTable;
    bool CheckFullness(void);
    void ResizeTable(void);
    int HashBrown(int key);
    int HashBrown(std::string key);
    
    bool IsPrime(unsigned int n) const;
    bool InsertTable(K key, dataItem<K, V> *item);

public:
    HashTable();     
    ~HashTable();
    V GetData(K key);
    bool InsertData(K key, V value);
    dataItem<K, V> *DeleteData(K key);
    void PrintHT(void) const;
};
/* End HashTable.h */

/* Begin HashTable.cpp */
template<class K, class V>
HashTable<K, V>::HashTable() {
  for (int j = 0; j < htSize; ++j) { testTable.push_back(emptyItem); }
}

template<class K, class V>
HashTable<K, V>::~HashTable() {}

template<class K, class V>
bool HashTable<K, V>::CheckFullness() {
  int size = testTable.size();

    int keepCount = 0;
    for (int i = 0; i < size; ++i) {
        if (testTable[i]->hasData) { ++keepCount; }
    }
    return (keepCount == size);
}

// NOTE TO SELF: need to rehash values after resizing else indexing becomes 
//  Yes, I  think the hashing function's not doing its job
template<class K, class V>
void HashTable<K, V>::ResizeTable() {
    htSize *= 2;
    while (!IsPrime(htSize)) { ++htSize; }

    // Rather than making use of std::vector's resize method,
    // we'll extend using push_back calls. The compiler can optimise 
    // this for us if needed.
    for(int i = 0; i < htSize; ++i){
        testTable.push_back(emptyItem);
    }
}
template<class K, class V>
dataItem<K, V> *HashTable<K, V>::DeleteData(K key) {
  //create method here
}

template<class K, class V>
int HashTable<K, V>::HashBrown(int key) {
    return key%htSize;
}

template<class K, class V>
int HashTable<K, V>::HashBrown(std::string key) {
    int out = 0;
    for (auto c : key) out += (int) c;

    return (out%htSize);
}

template<class K, class V>
bool HashTable<K, V>::InsertData(K key, V value) {
  dataItem<K, V> *n = new dataItem<K, V>(key, value, true);
  InsertTable(key, n);
}

template<class K, class V>
bool HashTable<K, V>::InsertTable(K key, dataItem<K,V> *item) {
    int hash = HashBrown(key);

    if (CheckFullness()) { ResizeTable(); }

    while (testTable[hash]) {
        ++hash;
        hash %= htSize;
    }
    testTable[hash] = item;
    return true;
}

// This doesn't finish cleanly; investigate
template<class K, class V>
void HashTable<K, V>::PrintHT(void) const {

    for (auto &i : testTable) {
        if(i != nullptr)
            std::cout << i->data << "\t";
    }
    std::cout << std::endl;

    std::cout << "TABLE SIZE: " << htSize << std::endl; // DEBUG
}

template<class K, class V>
V HashTable<K, V>::GetData(K key) {
    int hash = HashBrown(key);
    return (testTable[hash] == nullptr ? V() : testTable[hash]->data);
}

// Utlity method!
template<class K, class  V>
bool HashTable<K, V>::IsPrime(unsigned int n) const {
    if (n <= 1) { return false; }
    else if (n <= 3) { return true; }
    else if (n % 2 == 0 || n % 3 == 0) { return false; }
    
    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) { return false; }
        i += 6;
    }
    return true;
}

int main(void) {
    HashTable<int, int> htable;
    htable.PrintHT();

    htable.InsertData(3, 42);
    htable.InsertData(4, 413);
    htable.InsertData(5, 3123);
    htable.PrintHT();

    return 0;
}

/* End HashTable.cpp */
