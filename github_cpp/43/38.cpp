#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void bucket_sort(vector<double>&);
void insertion_sort(vector<double>&);
void print_vector(const vector<double>&);

int main(int argc, char const *argv[]) {
    double arr[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    vector<double> vec(arr, arr + sizeof(arr)/sizeof(arr[0]));
    bucket_sort(vec);
    print_vector(vec);
    return 0;
}

void print_vector(const vector<double> &vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void insertion_sort(vector<double> &vec) {
    for (int j = 1; j < vec.size(); j++) {
        double key = vec[j];
        int i = j - 1;
        while (i >= 0 && vec[i] > key) {
            vec[i + 1] = vec[i];
            i--;
        }
        vec[i + 1] = key;
    }
}

void bucket_sort(vector<double> &vec) {
    int n = vec.size();
    vector<vector<double>> bucket(n);
    for (int i = 0; i < n; i++) {
        bucket[(int)floor(n * vec[i])].push_back(vec[i]);
    }
    for (int i = 0; i < n; i++) {
        insertion_sort(bucket[i]);
    }
    int k = 0;
    for (int i = 0; i < bucket.size(); i++) {
        for (int j = 0; j < bucket[i].size(); j++) {
            vec[k++] = bucket[i][j];
        }
    }
}
