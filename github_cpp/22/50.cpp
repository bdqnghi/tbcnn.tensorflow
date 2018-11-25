

#include "bucket.hpp"



void sortBucket() {
    srand(time(NULL));
    const int ARRAY_LEN = 10;
    const int INT_RANGE = 100;
    
    
    const int RAD = INT_RANGE / 10;

    int *array = new int[ARRAY_LEN];
    for (int i = 0; i < ARRAY_LEN; i++) {
        array[i] = rand() % INT_RANGE;
    }

    
    message(array, ARRAY_LEN);
    bucket_sort(array, ARRAY_LEN, RAD);
    message(array, ARRAY_LEN);
}



int main(int argc, char const *argv[]) {
    sortBucket();
    return 0;
}
