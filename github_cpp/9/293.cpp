/**
 *  Author: Nhat M. Nguyen
 *  Date: 04-02-18
**/

#include <iostream>


using namespace std;


void insertion_sort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i;
        while ((j > 0) && (a[j - 1] > key)) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = key;
    }
}


int main() {
    int a[]  = {3, 2, 6, 8, 0, 9, 1, 5, 4, 7};
    int n = sizeof(a) / sizeof(a[0]);
    insertion_sort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}
