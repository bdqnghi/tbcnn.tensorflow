




























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


