



#ifndef CPP_ARITHMETIC_MERGE_SORT_H
#define CPP_ARITHMETIC_MERGE_SORT_H

using namespace std;
namespace mergeSort {

    template<typename T>
    void __merge(T arr[], int l, int mid, int r) {
        T *aux = new T[r - l + 1];

        for (int i = l; i <= r; i++) {
            aux[i - l] = arr[i];
        }

        int i = l, j = mid + 1;
        for (int k = l; k <= r; k++) {
            if (i > mid) {
                arr[k] = aux[j - l];
                j++;
            } else if (j > r) {
                arr[k] = aux[i - l];
                i++;
            } else if (aux[i - l] < aux[j - l]) {
                arr[k] = aux[i - l];
                i++;
            } else {
                arr[k] = aux[j - l];
                j++;
            }

        }

        delete[] aux;

    }

    template<typename T>
    void _mergeSort(T arr[], int l, int r) {
        if (l >= r)
            return;
        int mid = (l + r) / 2;
        _mergeSort(arr, l, mid);
        _mergeSort(arr, mid + 1, r);

        __merge(arr, l, mid, r);


    }

    template<typename T>
    void mergeSort(T arr[], int n) {
        _mergeSort(arr, 0, n - 1);
    }
}
#endif 
