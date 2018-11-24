#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void bubble_sort(vector<float>&);
void print_vector(const vector<float>&);

int main(int argc, char const *argv[]) {
    float arr[] = {5, 2, 7, 4, 9, 1, 3, 6, 8};
    vector<float> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    bubble_sort(vec);
    print_vector(vec);
    return 0;
}

void print_vector(const vector<float> &vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void bubble_sort(vector<float> &vec) {
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = vec.size() - 1; j > i; j--) {
            if (vec[j] < vec[j - 1]) {
                float tmp = vec[j];
                vec[j] = vec[j - 1];
                vec[j - 1] = tmp;
            }
        }
    }
}
