class LRUCache{
public:
    struct ListNode {
        int key, val;
        ListNode *prev;
        ListNode *next;
        ListNode(int k, int v) : key(k), val(v), prev(NULL), next(NULL) {}
    };
    int size, cap;
    ListNode *head;
    ListNode *tail;
    map<int, ListNode*> hash;
    LRUCache(int capacity) {
        size = 0;
        cap = capacity;
        head = new ListNode(0, 0);
        tail = new ListNode(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    void modify(ListNode *cur) {
        ListNode *prev_tail = tail->prev;
        prev_tail->next = cur;
        cur->prev = prev_tail;
        cur->next = tail;
        tail->prev = cur;
    }

    void delete_node(ListNode* cur) {
        ListNode *prev_cur = cur->prev;
        ListNode *next_cur = cur->next;
        prev_cur->next = next_cur;
        next_cur->prev = prev_cur;
    }

    int get(int key) {
        if (hash.find(key) == hash.end()) return -1;
        ListNode *temp = hash[key];
        delete_node(temp);
        modify(temp);
        return temp->val;
    }

    void set(int key, int value) {
        if (hash.find(key) != hash.end()) {
            ListNode *temp = hash[key];
            temp->val = value;
            delete_node(temp);
            modify(temp);
        } else {
            ListNode *cnt = new ListNode(key, value);
            hash.insert(make_pair(key, cnt));
            if (size == cap) {
                int dk = head->next->key;
                hash.erase(dk);
                delete_node(head->next);
                modify(cnt);
            } else {
                size ++;
                modify(cnt);
            }
        }
    }
};

