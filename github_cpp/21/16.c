

#include "selection.hpp"



void sortSelection() {
    srand(time(NULL));
    const int ARRAY_LEN = 20;
    const int INT_RANGE = 100;
    int *array = new int[ARRAY_LEN];
    
    for (int i = 0; i < ARRAY_LEN; i++) {
        array[i] = rand() % INT_RANGE;
    }

    
    message(array, ARRAY_LEN);
    selection_sort(array, ARRAY_LEN);
    message(array, ARRAY_LEN);
}



int main(int argc, char const *argv[]) {
    sortSelection();
    return 0;
}
