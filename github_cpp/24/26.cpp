

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l)/2;

        
        if (arr[mid] == x) return mid;

        
        
        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        
        return binarySearch(arr, mid+1, r, x);
    }

    return -1;
}

int main(int argc, char const *argv[]) {
    int arr[] = {3,5,12,56,92,123,156,190,201,222};
    int a = 12;
    int n = sizeof(arr)/ sizeof(arr[0]);
    cout<<"Binary Search :: "<<binarySearch(arr, 0, n-1, a)<<endl;
    return 0;
}
