// Example program
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void bucketSort(float a[], int size) {
    vector<float> bv[size];
    
    //inserting elements into the bucket
    for(int i=0;i<size;i++){
        int bi = size*a[i];        
        bv[bi].push_back(a[i]);
    }

    //sorting each bucket
    for(int i=0;i<size;i++){
        sort(bv[i].begin(), bv[i].end());
    }

    //traversing to load back
    int index = 0;
    for(int i=0;i<size;i++){
        for(int j=0; j< bv[i].size(); j++) {
            a[index++] = bv[i][j];
        }
    }
}

int main()
{
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr)/sizeof(arr[0]);
    bucketSort(arr, n);
 
    cout << "Sorted array is \n";
    for (int i=0; i<n; i++)
       cout << arr[i] << " ";
       
    return 0;
}
