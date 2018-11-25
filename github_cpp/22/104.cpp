







#include "BucketSort.hpp"

template <typename t>
void bucket_sort<t>::bsort(t*  a,int l,const t min,const t max,const double load) {
    int s = std::ceil((max-min+1)*load);                                                    

    std::vector<t> *buckets = new std::vector<t>[s];
    
    
    
    
    for (int i=0; i<l; i++) {
        t   e = a[i];
        int b = ((e-min)*load);                                                             
        buckets[b].push_back(e);
    }
    delete [] a;
    
    
    
    if (load != 1) {
        for (int i=0; i<s; i++)
            std::sort(buckets[i].begin(), buckets[i].end());
    }
    
    
    
    a = new t[l];
    for (int i=0,j=0; i<s; i++) {
        for (auto it=buckets[i].begin(); it!=buckets[i].end(); it++,j++) {
            a[j] = *it;
        }
    }
    
    delete [] buckets;
    
}

