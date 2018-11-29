//
//  BubbleSort.cpp
//  
//
//  Created by Vyas on 10/17/17.
//
//

#include <iostream>
#include <stdlib.h>
using namespace std;
class BubbleSort {
private:
    int *arr;
    int size;
public:
    BubbleSort(int *arr, int size);
    void sort();
    void printarr();
    ~BubbleSort();
};

BubbleSort::BubbleSort(int *a, int s) {
    arr = (int *)malloc(s * sizeof(int));
    int i = 0;
    for(i = 0; i < s; i++) {
        arr[i] = a[i];
    }
    size = s;
}

BubbleSort::~BubbleSort() {
    if(arr) {
        free(arr);
    }
}

void
BubbleSort::sort() {
    for (int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            if (*(arr+i) > *(arr+j)) {
                int tmp = *arr+i;
                *(arr+i) = *(arr+j);
                *(arr+ j) = tmp;
            }
        }
    }
}

void
BubbleSort::printarr() {
    for (int i = 0; i < size; i++) {
        cout << *(arr+i) << " ";
    }
    cout << endl;
}

int main() {
    int inp[11] = {23,33,12,1,24,664,32,11,2,0,123};
    BubbleSort b(inp, 11);
    b.printarr();
    b.sort();
    b.printarr();
    return 0;
}

