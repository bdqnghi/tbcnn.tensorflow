#include <functional>
#include <algorithm>
#include <mutex>
#include <thread>
#include "BucketSort.h"

//function that is used to sort the vector numbersToSort using a bucket sort like way
void BucketSort::sort(unsigned int numCores) {

    //create my 9 buckets to work with and a mutex to lock the bucket numbers
    std::vector<std::vector<unsigned int>> buckets{9};
    int bucketNum = 9;
    std::mutex bucketLock;

    //function used to sort out the numbers in the smaller buckets
    std::function<void(unsigned int)> sortBucket;
    sortBucket = [&bucketLock, &bucketNum, &buckets, &sortBucket](unsigned int x) {

        //locks so that way multiple things can't change bucketNum at once
        bucketLock.lock();
        bucketNum--;
        bucketLock.unlock();
        int k = bucketNum;
        //if valid, sort the bucket, otherwise the thread will die
        if (bucketNum >= 0){
            std::sort(buckets[k].begin(), buckets[k].end());
            sortBucket(x);
        }
    };


    //sort the numbers in the array into their buckets
    for (auto x = numbersToSort.begin(); x != numbersToSort.end(); ++x){
        unsigned int a = *x;

        //work out the starting digit of each number
        //optimised that way it can bring larger numbers down quicker
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

        //place in the correct bucket - a can never be 0, so need to shift everything down 1
        buckets[a-1].push_back(*x);
    }

    //create the vector of threads to store the threads in
    std::vector<std::thread> threads;

    //start the threads running
    for (unsigned int x = 1; x < numCores; ++x){
        threads.push_back(std::thread(sortBucket, x));
    }

    //do something with the current core this function has
    sortBucket(0);

    //join all the threads back together
    for (auto& t: threads){
        t.join();
    }

    //restore the sorted numbers into the array in their sorted order
    int y = 0;
    for (int x = 0; x < 9; x++){
        for (auto i: buckets[x]){
            numbersToSort[y] = i;
            y++;
        }
    }
}