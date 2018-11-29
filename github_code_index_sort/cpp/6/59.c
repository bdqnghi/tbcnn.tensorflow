#include "RadixSort.h"


/* http://www.geeksforgeeks.org/radix-sort/ */
int RadixSort::getMax(int *array, int n) {
    int mx = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > mx)
            mx = array[i];
    return mx;
}

/* http://www.geeksforgeeks.org/radix-sort/ */
void RadixSort::countSort(int *array, int n, int exp) {
    int output[n]; // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++) {
        count[(array[i] / exp) % 10]++;
    }

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++) {
        array[i] = output[i];
    }
}

/* http://www.geeksforgeeks.org/radix-sort/ */
void RadixSort::sort(int *array, int n) const {
    // Find the maximum number to know number of digits
    int m = getMax(array, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(array, n, exp);
    }
}



