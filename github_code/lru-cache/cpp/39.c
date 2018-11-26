/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file LRUCache.cpp
 * @author gewu(com@baidu.com)
 * @date 2015/06/15 09:13:50
 * @brief 
 *  
 **/

#include <iostream>
#include <list>
#include <map>

using namespace std;

struct CacheNode{
    int key;
    int value;
    CacheNode(int k, int v):key(k), value(v){}
};

class LRUCache{
public:
    LRUCache(int capacity){
        size = capacity;
    }
    int get(int key){
        if (cacheMap.find(key) == cacheMap.end()){
            return -1;
        }else {
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
            return cacheMap[key]->value;
        }
    }

    void set(int key, int value){
        if (cacheMap.find(key) == cacheMap.end()){
            if (cacheList.size() == size){
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }

            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
        else {
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }

private:
    list<CacheNode> cacheList;
    map<int, list<CacheNode>::iterator> cacheMap;
    int size;

};

/*
class LRUCache{
pulic:
    LRUCache(){
        
    }
    
    int get(int key){
        if (cacheMap.find(key) == cacheMap.end()){
            return -1;
        }else {
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
            return cacheMap[key]->value;
        }
    }

    void set(int key, int value){
        if (cacheMap.find(key) == cacheMap.end()){
            if (cacheList.size() == size){
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }

            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
        else {
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.beging();
        }
    }
    
private:
    list<CacheNode> cacheList;
    map<int, list<CacheNode>::iterator> cacheMap;
    int size;
};*/

int main(){
}



















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
