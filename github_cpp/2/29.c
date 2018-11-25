







#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache{
    
    
    
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
    
    
    void touch(int key) {
        
        buckets.splice(buckets.begin(), buckets, bucketOfKey[key]);
        bucketOfKey[key] = buckets.begin();
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        if (!bucketOfKey.count(key)) {
            if (buckets.size() == capacity) { 
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



int main(int argc, const char * argv[]) {
    LRUCache cache(2);
    cout << cache.get(5) << endl;
    cache.set(5, 5);
    cout << cache.get(5) << endl;
    
    return 0;
}
