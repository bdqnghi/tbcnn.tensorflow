/* Binary search implementation */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
bool search(vector<T>& vec, const T& key);

int main(void) {
    vector<int> ivec{3, 2, 6, 4, 8, 7, 0, 9, 1};
    cout << search(ivec, 4) << endl;

    return 0;
}

template <typename T>
bool search(vector<T>& vec, const T& key) {
    typename vector<T>::iterator begin = vec.begin(), mid = begin, end = prev(vec.end());
    sort(vec.begin(), vec.end());

    while(begin <= end) {
        mid = begin;
        advance(mid, distance(begin, end) / 2);

        if(*mid == key)
            return true;

        if(*mid > key)
            end = prev(mid);
        else
            begin = next(mid);
    }

    return false;
}
