#ifndef HEAPSORT_H
#define HEAPSORT_H


#include <iostream>
#include <vector>
    using std::vector;
 
// To heapify a subtree rooted with node root which is
// an index in vector. 
void heapify(vector<int> v, int root, int count){
    int largest = root;  // Initialize largest as root
    int left    = 2 * root + 1;  
    int right   = 2 * root + 2; 
 
    // If left child is larger than root
    if (left < v.size() && v[left] > v[largest]){
        largest = left;
        ++count; //increment count
    }
 
    // If right child is larger than largest so far
    if (right < v.size() && v[right] > v[largest]){
        largest = right;
        ++count; //increment count
    }
 
    // If largest is not root
    if (largest != root){
        swap(v[root], v[largest]);
        ++count;
 
        // Recursive heapify
        heapify(v, v.size(), largest);
    }
}
 
void heapsort(vector<int> v, int count){
    // Build heap (rearrange vector)
    for (int root = v.size() / 2 - 1; root >= 0; --root){
        heapify(v, root, count);
    }
 
    // One by one extract an element from heap
    for (int root = v.size() - 1; root >= 0; --root){
        // Move current root to end
        swap(v[0], v[root]);
 
        // call max heapify on the reduced heap
        heapify(v, root, count);
    }
}

#endif
