#include <iostream>

using std::cout;
using std::endl;

void print_list(int size, int list[]) {
    cout << "( ";
    for (int i = 0; i < size; i++)
        cout << list[i] << " ";
    cout << ")\n";
}


void selection_sort(int size, int list[]) {

    
    for (int a = 0; a < size; a++) {

        
        
        int min = a;
        for (int b = a; b < size; b++)
            if (list[b] < list[min])
                min = b;

        
        
        if (a != min) {
            int temp = list[a];
            list[a] = list[min];
            list[min] = temp;
        }
    }
}


int main() {
    int list[] = { 5,5,3,6,89,9,4,2,78,34, };
    const int size = sizeof(list)/sizeof(int);

    print_list(size, list);
    selection_sort(size, list);
    print_list(size, list);

    return 0;
}
