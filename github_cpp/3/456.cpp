#include <map>
using namespace std;

struct DoubleList{
    int key;
    int val;
    DoubleList *next, *pre;
    DoubleList():next(NULL), pre(NULL){}
    DoubleList(int key, int val):key(key), val(val), next(NULL), pre(NULL){
    }
};

class LRUCache{
private:
    DoubleList *head, *tail;
    map<int, DoubleList*> M;
    int capacity;
public:
    LRUCache(int capacity):capacity(capacity) {
        head = new DoubleList();
        tail = new DoubleList();
        head->next = tail;
        tail->pre = head;
    }
    void disConnect(DoubleList* cur){
        cur->pre->next = cur->next;
        cur->next->pre = cur->pre;
    }
    void insertHead(DoubleList* cur){
        cur->next = head->next;
        head->next->pre = cur;
        
        head->next = cur;
        cur->pre = head;
    }
    int get(int key) {
        if (M.find(key) == M.end()) return -1;
        else{
            DoubleList* cur = M[key];
            if (cur != head->next){
                disConnect(cur);
                insertHead(cur);
            }
            return cur->val;
        }
    }
    
    void eraseLast(){
        DoubleList* erase = tail->pre;
        M.erase(erase->key); // !!!
        
        erase->pre->next = tail;
        tail->pre = erase->pre;
        
        free(erase);
    }
    void add(int key, int value){
        DoubleList* cur = new DoubleList(key, value);
        M[key] = cur;
        insertHead(cur);
    }
    void set(int key, int value) {
        if (M.find(key) == M.end()){
            if (M.size() == capacity)
                eraseLast();
            add(key, value);
        }else {
            DoubleList* cur = M[key];
            disConnect(cur);
            insertHead(cur);
            cur->val = value;
        }
    }
};
