/* 
 * Illustrating the Bubblesort algorithm
 * 
 * Timing Complexity:
 * Best/Average/Worse: O(n^2)
 *
*/

#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;
 

const int N = 6;

int build_array(int *id);
int print_array(int *id);
int bubble_sort(int *id);

int main() {
    int id[N];
    build_array(id);
    cout << "Building the array...." << endl;
    print_array(id);
    bubble_sort(id);
    return 0;
}

int build_array(int *id) {
    srand(time(0)); //use current time as seed for random generator
    for (int i = 0; i < N; i++) {
        cout << "Enter a number: ";
        cin >> id[i];
    }
}

int print_array(int *id) {
    cout << "Printing array" << endl << "|   ";
    for (int i = 0; i < N; i++) {
        cout << id[i] << "   |   ";
    }
    cout << endl << "-----------------" << endl;
}

int bubble_sort(int *id) {
    int swapped = 0;
    for (int i = 0; i < N; i++) {
        // nest loop since we always get 
        for (int j = 0; j < (N-1); j++) {
            if (id[j] > id[j+1]) {
                swap(id[j], id[j+1]);
                swapped = 1;
            }
            print_array(id);
        }
    }
}
