#include <iostream>

using std::cout;
using std::endl;

void print_list(int size, int list[]) {
    cout << "( ";
    for (int i = 0; i < size; i++)
        cout << list[i] << " ";
    cout << ")\n";
}

// SECTION BEGIN selection-sort
void selection_sort(int size, int list[]) {

    // for each element in the list, in order from left to right
    for (int a = 0; a < size; a++) {

        // find the minimum element between that element and the end of the
        // list (inclusive)
        int min = a;
        for (int b = a; b < size; b++)
            if (list[b] < list[min])
                min = b;

        // if that element is not the minimum element, swap it with the minimum
        // element
        if (a != min) {
            int temp = list[a];
            list[a] = list[min];
            list[min] = temp;
        }
    }
}
// SECTION END selection-sort

int main() {
    int list[] = { 5,5,3,6,89,9,4,2,78,34, };
    const int size = sizeof(list)/sizeof(int);

    print_list(size, list);
    selection_sort(size, list);
    print_list(size, list);

    return 0;
}
