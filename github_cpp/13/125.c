

#include "bubble.hpp"



void sortBubble() {
    srand(time(NULL));
    const int ARRAY_LEN = 40;
    const int INT_RANGE = 1000;
    int *array = new int[ARRAY_LEN];

    for (int i = 0; i < ARRAY_LEN; i++) {
        array[i] = rand() % INT_RANGE;
    }

    message(array, ARRAY_LEN);
    bubble_sort(array, ARRAY_LEN);
    message(array, ARRAY_LEN);
}



int main(int argc, char const *argv[]) {
    sortBubble();
    return 0;
}
