



#include "bucketsort.h"
#include "string.h"
#include "datastruct/Link.h"

void bucketsort(int *arrayA, int arraySize, int range) {
    int *arrayC = new int[range];
    memset(arrayC, 0, sizeof(int) * (range));
    int i, j, k;
    for (i = 0; i < arraySize; i++) {
        arrayC[arrayA[i]]++;
    }

    for (i = j = 0; i < range; i++, j = k) {
        for (k = j; k < j + arrayC[i]; k++) {
            arrayA[k] = i;
        }
    }
}

void bucketsortMul(int* array, int arraySize, int range){
    int bucketCount = range/ 5;
    Link links[bucketCount];

    for(int i = 0; i< arraySize; i++){

    }
}