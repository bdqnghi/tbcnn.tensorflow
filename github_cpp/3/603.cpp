//
// Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
//
//
//
// get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
// put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
//
//
// Follow up:
// Could you do both operations in O(1) time complexity?
//
// Example:
//
// LRUCache cache = new LRUCache( 2 /* capacity */ );
//
// cache.put(1, 1);
// cache.put(2, 2);
// cache.get(1);       // returns 1
// cache.put(3, 3);    // evicts key 2
// cache.get(2);       // returns -1 (not found)
// cache.put(4, 4);    // evicts key 1
// cache.get(1);       // returns -1 (not found)
// cache.get(3);       // returns 3
// cache.get(4);       // returns 4
//
//


typedef struct LinkNode {
    int key;
    int value;
    LinkNode *next;
    LinkNode *prev;
    
    LinkNode(int k, int v) {
        key = k;
        value = v;
        next = NULL;
        prev = NULL;
    }
}*pLinkNode;

class LRUCache {
private:
    int cap;
    int count;
    pLinkNode begin;
    pLinkNode end;
    unordered_map<int, pLinkNode> m;
    
    void useNode(pLinkNode node) {
        if(node == end) return;
        pLinkNode prev_node = node->prev;
        pLinkNode next_node = node->next;
        end->next = node;
        node->prev = end;
        node->next = NULL;
        end = node;
        if(prev_node == NULL)
            begin = next_node;
        else
            prev_node->next = next_node;
        next_node->prev = prev_node;
    }
    
public:
    LRUCache(int capacity) {
        cap = capacity;
        count = 0;
        begin = NULL;
        end = NULL;
    }
    
    int get(int key) {
        auto it = m.find(key);
        if(it == m.end())
            return -1;
        pLinkNode cur = it->second;
        useNode(cur);
        return cur->value;
    }
    
    void put(int key, int value) {
        auto it = m.find(key);
        if(it != m.end()) {
            pLinkNode pn = it->second;
            pn->value = value;
            useNode(pn);
            return;
        }
        pLinkNode node = new LinkNode(key, value);
        m[key] = node;
        if(begin == NULL) {
            begin = node;
            end = node;
            count = 1;
        }
        else {
            end->next = node;
            node->prev = end;
            end = node;
            if(count < cap) {
                count++;
            }
            else {
                pLinkNode old = begin;
                begin = begin->next;
                begin->prev = NULL;
                m.erase(old->key);
                delete old;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
