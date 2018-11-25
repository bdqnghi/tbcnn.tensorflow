#ifndef HEAPSORT_H
#define HEAPSORT_H


#include <iostream>
#include <vector>
    using std::vector;
 


void heapify(vector<int> v, int root, int count){
    int largest = root;  
    int left    = 2 * root + 1;  
    int right   = 2 * root + 2; 
 
    
    if (left < v.size() && v[left] > v[largest]){
        largest = left;
        ++count; 
    }
 
    
    if (right < v.size() && v[right] > v[largest]){
        largest = right;
        ++count; 
    }
 
    
    if (largest != root){
        swap(v[root], v[largest]);
        ++count;
 
        
        heapify(v, v.size(), largest);
    }
}
 
void heapsort(vector<int> v, int count){
    
    for (int root = v.size() / 2 - 1; root >= 0; --root){
        heapify(v, root, count);
    }
 
    
    for (int root = v.size() - 1; root >= 0; --root){
        
        swap(v[0], v[root]);
 
        
        heapify(v, root, count);
    }
}

#endif
