/*
 * A simple LRU cache
 *
 *
 * Thanks Hawstein(http://hawstein.com/posts/lru-cache-impl.html) and
 *        Jian Lu (http://www.cs.uml.edu/~jlu1/doc/codes/lruCache.html)
 */

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
      if(node) { // node exists
        detach(node);
        node->data = data;
        attach(node);
      } else {
        if(_free_entries.empty()) {// cache is full
          node = _tail->prev;
          detach(node);
          _hashmap.erase(node->key);
        } else { //get a free node from _free_entries
          node = _free_entries.back();
          _free_entries.pop_back();
        }
        node->key = key; //put into hashmap and insert into link
        node->data = data;
        _hashmap[key] = node;
        attach(node);
      }
    }

    T Get(K key) {
      LRUCacheEntry<K,T> *node = _hashmap[key];
      if(node) { // hit
        detach(node);
        attach(node);
        return node->data;
      }
      else { // fail to hit
        return T();
      }
    }

  private:
    // detach nodes
    void detach(LRUCacheEntry<K,T>* node) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
    // insert the node into head
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
