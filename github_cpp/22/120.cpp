#include <functional>
#include <algorithm>
#include <mutex>
#include <thread>
#include "BucketSort.h"


void BucketSort::sort(unsigned int numCores) {

    
    std::vector<std::vector<unsigned int>> buckets{9};
    int bucketNum = 9;
    std::mutex bucketLock;

    
    std::function<void(unsigned int)> sortBucket;
    sortBucket = [&bucketLock, &bucketNum, &buckets, &sortBucket](unsigned int x) {

        
        bucketLock.lock();
        bucketNum--;
        bucketLock.unlock();
        int k = bucketNum;
        
        if (bucketNum >= 0){
            std::sort(buckets[k].begin(), buckets[k].end());
            sortBucket(x);
        }
    };


    
    for (auto x = numbersToSort.begin(); x != numbersToSort.end(); ++x){
        unsigned int a = *x;

        
        
        while (a / 100000 > 0) {
            a = a / 100000;
        }

        while (a / 10000 > 0) {
            a = a / 10000;
        }
        while (a / 1000 > 0) {
            a = a / 1000;
        }
        while (a / 100 > 0) {
            a = a / 100;
        }

        while (a / 10 > 0) {
            a = a / 10;
        }

        
        buckets[a-1].push_back(*x);
    }

    
    std::vector<std::thread> threads;

    
    for (unsigned int x = 1; x < numCores; ++x){
        threads.push_back(std::thread(sortBucket, x));
    }

    
    sortBucket(0);

    
    for (auto& t: threads){
        t.join();
    }

    
    int y = 0;
    for (int x = 0; x < 9; x++){
        for (auto i: buckets[x]){
            numbersToSort[y] = i;
            y++;
        }
    }
}