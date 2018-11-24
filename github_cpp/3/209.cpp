//
//  lru-cache
//  https://leetcode.com/problems/lru-cache/
//
//  Created by smilingpoplar on 15/6/5.
//  Copyright (c) 2015年 YangLe. All rights reserved.
//

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache{
    // 1. 按key分桶，每桶只要存key和value
    // 2. 映射：key=>列表中的key桶
    // 3. 每次访问把桶移到列表头，删除lru时只要删除表尾
    struct Bucket { int key; int value; };
    list<Bucket> buckets;
    unordered_map<int, list<Bucket>::iterator> bucketOfKey;
    int capacity;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (!bucketOfKey.count(key)) return -1;
        touch(key);
        return bucketOfKey[key]->value;
    }
    
    // 把桶移到列表头，更新哈希表中的映射
    void touch(int key) {
        // toList.splice(toListIterator, fromList, fromListSingleIterator)
        buckets.splice(buckets.begin(), buckets, bucketOfKey[key]);
        bucketOfKey[key] = buckets.begin();
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        if (!bucketOfKey.count(key)) {
            if (buckets.size() == capacity) { // 删除链表尾
                bucketOfKey.erase(buckets.back().key);
                buckets.pop_back();
            }
            buckets.push_front({key, value});
            bucketOfKey[key] = buckets.begin();
        } else {
            bucketOfKey[key]->value = value;
            touch(key);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */

int main(int argc, const char * argv[]) {
    LRUCache cache(2);
    cout << cache.get(5) << endl;
    cache.set(5, 5);
    cout << cache.get(5) << endl;
    
    return 0;
}
