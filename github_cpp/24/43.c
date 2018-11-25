







#ifndef __CPP_Algorithms__BinarySearch__
#define __CPP_Algorithms__BinarySearch__

#include <iostream>
#include <vector>
#include "VectorUtility.hpp"

template <typename T>
class BinarySearch {
public:
    static bool binarySearch(std::vector<T> &vector, T target);
    static bool recursiveBinarySearch(std::vector<T> &vector, T target);
    
private:
    static bool binarySearchRange(std::vector<T> &vector, int left, int right, T target);
};


template <typename T>
bool BinarySearch<T>::binarySearch(std::vector<T> &vector, T target)
{
    assert(VectorUtility<T>::vectorIsSorted(vector) && "BinarySearch should only be used with sorted input vectors.");
    
    int left = 0;
    int right = (int)vector.size() - 1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        if (vector[mid] > target) {
            right = mid - 1;
        }
        else if (vector[mid] < target) {
            left = mid + 1;
        }
        else {
            
            return true;
        }
    }
    
    return false;
}

template <typename T>
bool BinarySearch<T>::recursiveBinarySearch(std::vector<T> &vector, T target)
{
    assert(VectorUtility<T>::vectorIsSorted(vector) && "BinarySearch should only be used with sorted input vectors.");
    return binarySearchRange(vector, 0, (int)vector.size() - 1, target);
}

template <typename T>
bool BinarySearch<T>::binarySearchRange(std::vector<T> &vector, int left, int right, T target)
{
    if (left <= right) {
        int mid = (left + right) / 2;
        
        if (vector[mid] > target) {
            return binarySearchRange(vector, left, mid - 1, target);
        }
        else if (vector[mid] < target) {
            return binarySearchRange(vector, mid + 1, right, target);
        }
        else {
            
            return true;
        }
    }
    
    return false;
}

#endif 