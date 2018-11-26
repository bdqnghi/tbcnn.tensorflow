//
//  LRU.cpp
//  PAT Basic Level
//
//  Created by apple on 16/9/19.
//  Copyright © 2016年 zp1996. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
using namespace std;
struct Node
{
    string key;
    string value;
    Node* newer;
    Node* older;
    bool operator==(const Node& b)
    {
        return key == b.key &&
        value == b.value &&
        newer == b.newer && older == b.older;
    }
    Node(string k, string v, Node* n, Node* o)
    {
        key = k;
        value = v;
        newer = n;
        older = o;
    }
};
struct Cache
{
    int size = 0;
    int limit;
    Node* head;
    Node* tail;
    map<string, Node*> keymap;
    Cache(int l)
    {
        limit = l;
    }
};
Cache cache(5);
Node temp("temp", "temp", NULL, NULL);
Node* getNode (string key)
{
    map<string, Node*>::iterator it = cache.keymap.find(key);
    // 如果没有,则返回
    if (it == cache.keymap.end()) {
        return NULL;
    }
    Node* entry = cache.keymap[key];
    // 如果是尾部,则不操作
    if (entry == cache.tail) {
        return entry;
    }
    // 将其从本身位置拿出
    if (entry->newer) {
        if (entry == cache.head)
            cache.head = entry->newer;
        entry->newer->older = entry->older;
    }
    if (entry->older) {
        entry->older->newer = entry->newer;
    }
    // 将其放到尾部
    entry->newer = NULL;
    entry->older = cache.tail;
    if (cache.tail) {
        cache.tail->newer = entry;
    }
    cache.tail = entry;
    return entry;
}
Node* shiftNode ()
{
    Node* entry = cache.head;
    if (entry) {
        cache.head = cache.head->newer;
        cache.head->older = NULL;
        entry->newer = entry->older = NULL;
        cache.keymap.erase(entry->key);
        cache.size--;
    }
    return entry;
}
Node* putNode (string key, string value)
{
    Node* removed = NULL;
    Node* entry = getNode(key);
    // 需要插入,直接放到尾部
    if (!entry) {
        if (cache.size == cache.limit)
            removed = shiftNode();
        entry = new Node(key, "", NULL, NULL);
        cache.keymap[key] = entry;
        if (cache.tail) {
            cache.tail->newer = entry;
            entry->older = cache.tail;
        } else {
            cache.head = entry;
        }
        cache.tail = entry;
        cache.size++;
    }
    entry->value = value;
    entry = NULL;
    return removed;
}
void eachCache ()
{
    Node* node = cache.head;
    while (node) {
        string res = node->value;
        cout<<res<<endl;
        node = node->newer;
    }
    cout<<"loop is over"<<endl;
}
int main ()
{
    putNode("A", "A");
    putNode("B", "B");
    putNode("C", "C");
    putNode("D", "D");
    putNode("E", "E");
    putNode("R", "R");
    putNode("A", "A");
    putNode("C", "C");
    eachCache();
    return 0;
}

