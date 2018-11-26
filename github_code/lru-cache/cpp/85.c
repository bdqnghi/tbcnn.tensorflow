/*******************************************************************************
 *  @File  : 146_LRU_Cache.cpp
 *  @Author: Zhang Zixuan
 *  @Email : zixuan.zhang.victor@gmail.com
 *  @Blog  : www.noathinker.com
 *  @Date  : Mon 09 May 2016 03:35:03 PM CST
 ******************************************************************************/

/*
 * Question:
 *
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and set.
 *
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 *
 * set(key, value) - Set or insert the value if the key is not already present.
 * When the cache reached its capacity, it should invalidate the least recently
 * used item before inserting a new item.
 *
 */

#include <iostream>
#include <unordered_map>

using namespace std;

struct LRUNode
{
    int key;
    int val;
    LRUNode* pre;
    LRUNode* next;
    LRUNode(int k, int v) : key(k), val(v), pre(NULL), next(NULL){}
};

class LRUCache
{
public:
    LRUCache(int capacity)
    {
        current = 0;
        this->capacity = capacity;
        head = NULL;
        tail = NULL;
    }

    int get(int key)
    {
        unordered_map<int, LRUNode*>::iterator it = map.find(key);
        if (it == map.end())
            return -1;
        liftNode(it->second);
        return it->second->val;
    }

    void set(int key, int value)
    {
        unordered_map<int, LRUNode*>::iterator it = map.find(key);
        if (it == map.end())
        {
            if (this->capacity == 0)
                return ;
            if (current == capacity)
            {
                map.erase(tail->key);
                if (tail->pre != NULL)
                {
                    LRUNode* temp = tail->pre;
                    tail->pre->next = NULL;
                    delete tail;
                    tail = temp;
                }
                else
                {
                    delete tail;
                    tail = NULL;
                    head = NULL;
                }
            }
            else
                current++;
            LRUNode* newNode = new LRUNode(key, value);
            if (current == 1)
            {
                // First node in link
                head = newNode;
                tail = newNode;
            }
            else
            {
                head->pre = newNode;
                newNode->next = head;
                head = newNode;
            }
            map[key] = newNode;
        }
        else
        {
            it->second->val = value;
            liftNode(it->second);
        }
    }

    int display()
    {
        cout<<"CurentCount:"<<current<<".";
        LRUNode* pointer = head;
        while (pointer)
        {
            cout<<"["<<pointer->key<<","<<pointer->val<<"],";
            pointer = pointer->next;
        }
        cout<<"MapSize: "<<map.size();
        cout<<endl;
        return 0;
    }

private:
    int capacity;
    int current;
    unordered_map<int, LRUNode*> map;
    LRUNode* head;
    LRUNode* tail;

    void liftNode(LRUNode* node)
    {
        if (head == node)
            return;
        if (node == tail)
        {
            tail = tail->pre;
            tail->next = NULL;
        }
        else
        {
            node->pre->next = node->next;
            node->next->pre = node->pre;
        }
        head->pre = node;
        node->next = head;
        node->pre = NULL;
        head = node;
    }

};

void test1()
{
    cout<<"Test 1"<<endl;
    int capacity = 0;
    LRUCache lruCache(capacity);
    cout<<"Get 1. "<<lruCache.get(1)<<"\t";lruCache.display();cout<<endl;
    cout<<"Set 1,2. ";lruCache.set(1,2); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Set 4,3. ";lruCache.set(4,3); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Set 4,5. ";lruCache.set(4,5); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Set 1,6. ";lruCache.set(1,6); cout<<"\t"; lruCache.display(); cout<<endl;
}

void test2()
{
    cout<<"Test 2"<<endl;
    int capacity = 1;
    LRUCache lruCache(capacity);
    cout<<"Get 1. "<<lruCache.get(1)<<"\t";lruCache.display();cout<<endl;
    cout<<"Set 1,2. ";lruCache.set(1,2); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Get 1. "<<lruCache.get(1)<<"\t";lruCache.display();cout<<endl;
    cout<<"Set 4,3. ";lruCache.set(4,3); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Get 1. "<<lruCache.get(1)<<"\t";lruCache.display();cout<<endl;
    cout<<"Set 4,5. ";lruCache.set(4,5); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Get 4. "<<lruCache.get(4)<<"\t";lruCache.display();cout<<endl;
    cout<<"Set 1,6. ";lruCache.set(1,6); cout<<"\t"; lruCache.display(); cout<<endl;
    cout<<"Get 1. "<<lruCache.get(1)<<"\t";lruCache.display();cout<<endl;
}

void set(LRUCache& lruCache, int key, int value)
{
    cout<<"Set "<<key<<","<<value<<".";
    lruCache.set(key, value);
    cout<<"\t";
    lruCache.display();
}

void get(LRUCache& lruCache, int key)
{
    cout<<"Get "<<key<<". ";
    cout<<lruCache.get(key);
    cout<<"\t";
    lruCache.display();
}

void test3()
{
    cout<<"Test 3"<<endl;
    int capacity = 2;
    LRUCache lruCache(capacity);
    get(lruCache, 1);
    set(lruCache, 1, 2);
    get(lruCache, 1);
    set(lruCache, 4, 3);
    get(lruCache, 1);
    set(lruCache, 4, 5);
    get(lruCache, 4);
    set(lruCache, 1, 6);
    get(lruCache, 1);
    get(lruCache, 7);
    set(lruCache, 7, 3);
    get(lruCache, 7);
    get(lruCache, 1);
    get(lruCache, 4);
    set(lruCache, 3, 3);
    get(lruCache, 1);
}

void test4()
{
    cout<<"Test 4"<<endl;
    int capacity = 5;
    LRUCache lruCache(capacity);
    get(lruCache, 1);
    set(lruCache, 1, 2);
    set(lruCache, 4, 3);
    get(lruCache, 1);
    set(lruCache, 5, 3);
    set(lruCache, 3, 4);
    get(lruCache, 4);
    set(lruCache, 6, 7);
    set(lruCache, 7, 6);
    set(lruCache, 6, 6);
    set(lruCache, 8, 8);
    get(lruCache, 1);
    set(lruCache, 2, 2);
}

int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
