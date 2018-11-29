#include <iostream>
#include <vector>
#include <utility>

using std::cout;
using std::ostream;
using std::endl;
using std::vector;
using std::move;

template<typename T>
void insertionsort(vector <T> &v);

template<typename T>
ostream &operator<<(ostream &os, vector <T> &v);

int main() {
    // create the vector of items
    vector <int> v = {
        12,63,56,55,27,22,15,9,2,91,80,98,40,29,36,92,99,46,81,43,11,60,6,68,18,44,90,
        17,93,59,74,26,78,7,8,24,71,73,37,48,82,49,67,4,62,20,25,84,1,87,30,31,39,86,
        61,76,100,47,10,51,23,58,45,5,41,34,85,77,57,95,52,66,75,19,28,42,96,79,88,70,
        16,50,69,53,89,94,65,33,3,64,32,21,72,97,54,14,83,38,13,35
    };
    // print the unsorted vector
    cout << "Unsorted: \n";
    cout << v;
    cout << "\n";
    // sort the vector
    insertionsort(v);
    // print the sorted vector
    cout << "Sorted: \n";
    cout << v;

    return 0;
}

template<typename T>
void insertionsort(vector <T> &v) {
    for (int i = 1; i < v.size(); i++) {
        T temp = move(v[i]);
        int j = i - 1;
        while (j >= 0 && temp < v[j]) {
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(temp);
    }
}

// Shows the operator << how to print the vector
template<typename T>
ostream &operator<<(ostream &os, vector <T> &v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

