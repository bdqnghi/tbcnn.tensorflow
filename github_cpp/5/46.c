








#include <iostream>
#include "SORT_ALGORITHM.h"
using namespace std;

int main() {
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = 10 - i;
    }
    for (int i = 0; i < 10; i++) cout << "" << array[i] << " ";
    cout << endl;
    insertion_sort(array, 10);
    for (int i = 0; i < 10; i++) cout << "" << array[i] << " ";
    cout << endl;
    return 0;
}
