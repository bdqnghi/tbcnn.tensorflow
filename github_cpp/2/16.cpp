

#include <iostream>
#include <vector>
#include <ext/hash_map>
using namespace std;
using namespace __gnu_cxx;

template <class K, class T>
struct LRUCacheEntry {
  K key;
  T data;
  LRUCacheEntry *prev, *next;
};

template <class K, class T>
class LRUCache {

  public:
    LRUCache(size_t size) {
      _entries = new LRUCacheEntry<K,T>[size];

      for(int i=0; i<size; ++i) {
        _free_entries.push_back(_entries+i);
      }
      _head = new LRUCacheEntry<K,T>;
      _tail = new LRUCacheEntry<K,T>;
      _head->prev = NULL;
      _head->next = _tail;
      _tail->prev = _head;
      _tail->next = NULL;
    }

    ~LRUCache() {
      delete _head;
      delete _tail;
      delete[] _entries;
    }

    void Put(K key, T data) {
      LRUCacheEntry<K,T> *node = _hashmap[key];
      if(node) { 
        detach(node);
        node->data = data;
        attach(node);
      } else {
        if(_free_entries.empty()) {
          node = _tail->prev;
          detach(node);
          _hashmap.erase(node->key);
        } else { 
          node = _free_entries.back();
          _free_entries.pop_back();
        }
        node->key = key; 
        node->data = data;
        _hashmap[key] = node;
        attach(node);
      }
    }

    T Get(K key) {
      LRUCacheEntry<K,T> *node = _hashmap[key];
      if(node) { 
        detach(node);
        attach(node);
        return node->data;
      }
      else { 
        return T();
      }
    }

  private:
    
    void detach(LRUCacheEntry<K,T>* node) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
    
    void attach(LRUCacheEntry<K,T>* node) {
      node->prev = _head;
      node->next = _head->next;
      _head->next = node;
      node->next->prev = node;
    }

  private:
    hash_map<K, LRUCacheEntry<K,T>* > _hashmap;
    vector< LRUCacheEntry<K,T>* > _free_entries;
    LRUCacheEntry<K,T> *_head, *_tail;
    LRUCacheEntry<K,T> *_entries;
};

int main() {
  hash_map<int, int> map;

  map[9]= 999;
  cout << map[9] << endl;
  cout << map[10] << endl;
  LRUCache<int, string> lru_cache(100);
  lru_cache.Put(1, "one");
  cout << lru_cache.Get(1) << endl;

  if(lru_cache.Get(2) == "")
    lru_cache.Put(2, "two");
  cout << lru_cache.Get(2);

  return 0;
}
