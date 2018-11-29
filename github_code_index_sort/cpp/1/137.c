#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define SIZE 10
int arr[SIZE];

void insertionSort(int length);

int main() {
    int i;

    for (i = 0; i < SIZE; i++) {    // input
        arr[i] = rand() % 20;
    }

    insertionSort(SIZE);    // sort

    for (i = 0; i < SIZE; i++) {    // output
        cout << arr[i] << endl;
    }

    return 0;
}

void insertionSort(int length) {
      int i, j, tmp;
      for (i = 1; i < length; i++) {
            j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                  tmp = arr[j];
                  arr[j] = arr[j - 1];
                  arr[j - 1] = tmp;
                  j--;
            }
      }
}
