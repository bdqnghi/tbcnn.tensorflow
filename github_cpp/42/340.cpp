/**
 *  Author: Nhat M. Nguyen
 *  Date: 04-02-18
**/

#include <iostream>
#include <utility> //std::swap


using namespace std;


void selection_sort(int a[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int max_index = i;
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] > a[max_index]) {
                max_index = j;
            }
        }
        swap(a[i], a[max_index]);
    }
}


int main() {
    int a[]  = {3, 2, 6, 8, 0, 9, 1, 5, 4, 7};
    int n = sizeof(a) / sizeof(a[0]);
    selection_sort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}
