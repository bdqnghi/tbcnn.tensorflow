#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void radix_sort(vector<int>&);
void counting_sort(vector<int>&, int);
void print_vector(const vector<int>&);

int main(int argc, char const *argv[]) {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    vector<int> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    radix_sort(vec);
    print_vector(vec);
    return 0;
}

void print_vector(const vector<int> &vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void radix_sort(vector<int> &vec) {
    int max = vec[distance(vec.begin(), max_element(vec.begin(), vec.end()))];
    for (int i = 1; max / i > 0; i *= 10) {
        counting_sort(vec, i);
    }
}

void counting_sort(vector<int> &vec, int d) {
    vector<int> output(vec.size());
    vector<int> count(10, 0);
    for (int i = 0; i < vec.size(); i++) {
        count[ (vec[i]/d)%10 ]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = vec.size() - 1; i >= 0; i--) {
        output[count[ (vec[i]/d)%10 ] - 1] = vec[i];
        count[ (vec[i]/d)%10 ]--;
    }
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = output[i];
    }
}
