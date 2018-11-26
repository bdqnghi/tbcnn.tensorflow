// merge.cpp

// merge sort = O(n lg n)
// quick sort = O(n lg n)

#include "cosc121.h"
#include <iostream>
using namespace std;

void merge(int v[], int start, int mid, int end) {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 =  end - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++) {
        L[i] = v[start + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = v[mid + 1+ j];
    }
    i = 0;
    j = 0;
    k = start; 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            v[k] = L[i];
            i++;
        }
        else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int v[], int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(v, start, mid);
        mergeSort(v, mid + 1, end);
        merge(v, start, mid, end);
    }
}

int main(int argc, char const *argv[])
{
	int x[8] = {40, 80, 20, 60, 10, 70, 50, 30};
	print(x, 8);
	mergeSort(x, 0, 7);
	print(x, 8);
	return 0;
}