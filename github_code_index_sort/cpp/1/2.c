// insertion.cpp
/*
 * It has been a year or two since I even thought about these quadratic time 
 * sort algorithms...
 * Can I still write an insertion sort?
 */
#include <iostream>
using namespace std;

void insertion_sort(int a[], int size)
{
    int i, j, temp;

    for (i=1; i<size; i++) {
        for (j=i-1; j>-1 && a[j]>a[j+1]; j--) {
//        for (j=i-1; j>-1; j--) {
//            if (a[j]>a[j+1]) {
            temp = a[j];
            a[j] = a[j+1];
            a[j+1] = temp;
//            } else {
//                break;
//            }
        }
    }
}

int main()
{
    int i;
    int a[5] = {21,4,29,3,10};

    insertion_sort(a, 5);

    for (i=0; i<5; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}

