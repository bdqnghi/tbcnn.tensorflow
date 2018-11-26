/**
*   Design and implement a data structure for Least Recently Used (LRU) cache. 
*   It should support the following operations: get and set.
*
*   get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
*   set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, 
*   it should invalidate the least recently used item before inserting a new item.
*
**/

#include <iostream>
#include <map>

using namespace std;

class LRUCache{
public:
    struct CacheNode {
        CacheNode *next;
        CacheNode *prev;
        int key;
        int value;
        
        CacheNode(int k, int val) 
            : next(NULL)
            , prev(NULL)
            , key(k)
            , value(val) {}
    };
    
    LRUCache(int capacity) 
        : m_capacity(capacity)
        , m_head(NULL)
        , m_tail(NULL) {
    }
    
    ~LRUCache() {
    }
    
    int get(int key) {
        map<int, CacheNode*>::iterator it = m_lruCache.find(key);
        if (it == m_lruCache.end())
            return -1;

        //update the cache
        int value = it->second->value;
        set(key, value);
        return value;
    }
        
    void set(int key, int value) {
        map<int, CacheNode*>::iterator it = m_lruCache.find(key);
        if (it == m_lruCache.end()) {
            CacheNode *newCacheItem = new CacheNode(key, value);
            m_lruCache[key] = newCacheItem;
            newCacheItem->next = m_head;
            
            if (!m_tail)
                m_tail = newCacheItem;
                
            if (m_head)
                m_head->prev = newCacheItem;

            m_head = newCacheItem;
            
            if(m_lruCache.size() > m_capacity) {
                CacheNode *m = m_tail;
                m_lruCache.erase(m_tail->key);
                m_tail = m_tail->prev;
                if (m_tail)
                    m_tail->next = NULL;
                delete m;
            }
        } else {
            CacheNode *n = it->second;
            n->value = value;

            if (n == m_head)
                return;
                
            if(n->next)
                n->next->prev = n->prev;
            if (n->prev)
                n->prev->next = n->next;
             if (n == m_tail)
                m_tail = n->prev;
             if (m_head)
                m_head->prev = n;
             n->next=m_head;
             m_head = n;
        }    
    }
    
private:
    int m_capacity;
    CacheNode *m_head;
    CacheNode *m_tail;
    map<int, CacheNode*> m_lruCache;
};

int main()
{
    LRUCache lru(2);
    
    lru.set(2,1);
    lru.set(2,2);
    cout<<lru.get(2)<<" ";
    
    lru.set(1,1);
    lru.set(4,1);
    cout<<lru.get(2)<<" ";

    return 0;
}
