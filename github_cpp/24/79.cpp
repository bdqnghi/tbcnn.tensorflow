#ifndef BINARYSEARCH_CPP_
#define BINARYSEARCH_CPP_

#include "binarySearch.h"
#include <vector>


using namespace std;

template <class T>
int binarySearch(vector<T> &arr, int low, int high, T key){
	int mid = (low+high)/2;
    if(mid == low){
        if(arr[mid] == key){
            return low;
        }
        else return -1;
    }
    if(arr[mid] == key){
        for (; arr[mid] == key; mid--);
        return mid+1;
    }
    else if(arr[mid]>key){
        return binarySearch<T>(arr,low,mid,key);
    }
    else {
        return binarySearch<T>(arr,mid,high,key);
    }
}

#endif 