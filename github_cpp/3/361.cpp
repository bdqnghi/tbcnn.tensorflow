#include <map>

class LRUCache{
public:
    class ListNode {
    public:
        int val;
        ListNode *next, *prev;
        ListNode(int val) {
            this->val = val;
            this->next = NULL;
            this->prev = NULL;
        }
    };
    map<int, int> hash1;
    map<int, ListNode*> hash2;
    int cap, cur;
    ListNode *head, *tail;
    // @param capacity, an integer
    LRUCache(int capacity) {
        // write your code here
        cap = capacity;
        cur = 0;
        head = new ListNode(-1);
        tail = new ListNode(-1);
        head->next = tail;
        tail->prev = head;
    }
    void move(ListNode *cnt) {
        ListNode *cnt_next = cnt->next, *cnt_prev = cnt->prev;
        cnt_prev->next = cnt_next;
        cnt_next->prev = cnt_prev;
        ListNode *head_next = head->next;
        head->next = cnt;
        cnt->prev = head;
        cnt->next = head_next;
        head_next->prev = cnt;
    }
    void add(ListNode *cnt) {
        ListNode *head_next = head->next;
        head->next = cnt;
        cnt->prev = head;
        cnt->next = head_next;
        head_next->prev = cnt;
    }
    void solve(int key, int value) {
        int k = tail->prev->val;
        hash1.erase(k);
        hash2.erase(k);
        hash1.insert(make_pair(key, value));
        ListNode *p = tail->prev;
        p->val = key;
        move(p);
        hash2.insert(make_pair(key, p));
    }
    // @return an integer
    int get(int key) {
        // write your code here
        if (hash1.find(key) == hash1.end()) {
            return -1;
        } else {
            ListNode *res = hash2[key];
            move(res);
            return hash1[key];
        }
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    void set(int key, int value) {
        // write your code here
        if (hash1.find(key) != hash1.end()) {
            hash1[key] = value;
            get(key);
        } else {
            if (cur < cap) {
                ListNode *cnt = new ListNode(key);
                hash1.insert(make_pair(key, value));
                hash2.insert(make_pair(key, cnt));
                add(cnt);
                cur ++;
            } else {
                solve(key, value);
            }
        }
    }
};
