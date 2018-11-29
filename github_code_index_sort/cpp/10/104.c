//
//  BucketSort.cpp
//  BucketSort
//
//  Created by Demon on 10/04/16.
//  Copyright © 2016 victor choudhary. All rights reserved.
//

#include "BucketSort.hpp"

template <typename t>
void bucket_sort<t>::bsort(t*  a,int l,const t min,const t max,const double load) {
    int s = std::ceil((max-min+1)*load);                                                    // size of array

    std::vector<t> *buckets = new std::vector<t>[s];
    
    //std::cout << "starting bucketing : ";std::cin.get();
    
    // fill each element in its own bucket
    for (int i=0; i<l; i++) {
        t   e = a[i];
        int b = ((e-min)*load);                                                             // bucket position
        buckets[b].push_back(e);
    }
    delete [] a;
    //std::cout << "deleted buffer & completed bucketing";std::cin.get();
    
    // retrieve each element
    if (load != 1) {
        for (int i=0; i<s; i++)
            std::sort(buckets[i].begin(), buckets[i].end());
    }
    
    //std::cout << "completed sorting, now allocating space";std::cin.get();
    // put sorted list into its place
    a = new t[l];
    for (int i=0,j=0; i<s; i++) {
        for (auto it=buckets[i].begin(); it!=buckets[i].end(); it++,j++) {
            a[j] = *it;
        }
    }
    
    delete [] buckets;
    //std::cout << "flushed buckets";std::cin.get();
}

