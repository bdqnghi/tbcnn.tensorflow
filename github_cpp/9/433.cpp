#include "insertion-sort.hpp"
#include "vector"
#include "iostream"
#include "time.h"

using namespace std;

void insertionSort(vector<int> A){
    int n = A.capacity();
    cout<<"n: "<<n<<"\n";
    clock_t tStart = clock();
    for(int j=2; j<n;j++){
        int key = A[j];
        int i = j-1;
        while (i>=0 && A[i]>key){
            A[i+1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
    clock_t tEnd = clock();
    cout<<"sort took "<<(double)(tEnd - tStart)*1000/CLOCKS_PER_SEC<<" milliseconds to execute.\n";
    cout<<"A: [";
    for(int k=0;k<n;k++)
        cout<<A[k]<<" ";
    cout<<"]\n";
}
